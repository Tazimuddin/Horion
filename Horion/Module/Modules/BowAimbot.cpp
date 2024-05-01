#include "BowAimbot.h"

#include "../../../Utils/Target.h"
#include "../../DrawUtils.h"

std::vector<Entity*> targetList;

BowAimbot::BowAimbot() : IModule(0, Category::COMBAT, "Aimbot, but for bows.") {
	registerBoolSetting("Silent", &silent, silent);
	registerBoolSetting("Predict", &predict, predict);
	registerBoolSetting("Visualize", &visualize, visualize);
}

BowAimbot::~BowAimbot() {
}

struct CompareTargetEnArray {
	bool operator()(Entity* lhs, Entity* rhs) {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

const char* BowAimbot::getModuleName() {
	return "BowAimbot";
}

void findTargets(Entity* currentEntity, bool isRegularEntitie) {
	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 130) {
		targetList.push_back(currentEntity);
	}
}

void BowAimbot::onPostRender(MinecraftUIRenderContext* renderCtx) {
	targetList.clear();

	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr)
		return;

	if (localPlayer->getSelectedItemId() != 300)  // Bow in hand?
		return;

	if (!(GameData::isRightClickDown() && GameData::canUseMoveKeys())) // is aiming?
		return;

	Game.forEachEntity(findTargets);

	if (!targetList.empty()) {
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		Vec3 origin = Game.getClientInstance()->levelRenderer->getOrigin();  // TODO: sort list
		Entity* entity = targetList[0];
		Vec3 pos = entity->getAABBShapeComponent()->aabb.centerPoint();
		if (predict) {
			Vec3 velocity = entity->getPos()->sub(*entity->getPosOld());
			velocity.x *= origin.dist(pos) / 2.f;
			velocity.z *= origin.dist(pos) / 2.f;
			pos = pos.add(velocity);
		}
		if (visualize) {
			DrawUtils::setColor(.75f, .25f, .5f, 0.2f);
			DrawUtils::drawBox(pos.sub(0.5), pos.add(0.5), 0.3f, true);
		}
		pos = pos.sub(origin);
		float yaw = (atan2f(pos.z, pos.x) * DEG_RAD) - 90;
		float len = pos.magnitudexz();
		constexpr float g = 0.002f;  // nukkit = 0.012, some servers need different values
		float tmp = 1 - g * (g * (len * len) + 2 * pos.y);
		float pitch = DEG_RAD * -atanf((1 - sqrtf(tmp)) / (g * len));

		if (silent) {
			angle = Vec2(pitch, yaw);
			MovePlayerPacket p(Game.getLocalPlayer(), *Game.getLocalPlayer()->getPos());
			p.pitch = angle.x;
			p.yaw = angle.y;
			p.headYaw = angle.y;
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&p);
		} else {
			if (pitch < 89 && pitch > -89) {
				Vec2 angles = Vec2(pitch, yaw);

				Vec2 appl = angles.sub(localPlayer->getActorHeadRotationComponent()->rot).normAngles();
				appl.x = -appl.x;
				appl = appl.div(7);  // Smooth dat boi

				localPlayer->applyTurnDelta(&appl);
			}
		}
	}
}

void BowAimbot::onSendPacket(Packet* packet) {
	if (packet->isInstanceOf<MovePlayerPacket>() && silent) {
		if (!targetList.empty()) {
			auto* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
			movePacket->pitch = angle.x;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
		}
	}
}
