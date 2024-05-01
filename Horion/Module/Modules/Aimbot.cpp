#include "Aimbot.h"

Aimbot::Aimbot() : IModule(0, Category::COMBAT, "Automatically aims at the nearest entity.") {
	registerFloatSetting("Range", &range, range, 3.f, 8.f);
	registerBoolSetting("Mobs", &mobs, mobs);
	registerBoolSetting("Require Click", &click, click);
	registerBoolSetting("Only Swords/Axes", &sword, sword);
	registerBoolSetting("Vertical", &vertical, vertical);
	registerFloatSetting("Horizontal Speed", &horizontalspeed, horizontalspeed, 10.f, 90.f);
	registerFloatSetting("Vertical Speed", &verticalspeed, verticalspeed, 10.f, 90.f);
	registerFloatSetting("Horizontal Range", &horizontalrange, horizontalrange, 20.f, 180.f);
	registerFloatSetting("Vertical Range", &verticalrange, verticalrange, 20.f, 180.f);
	registerBoolSetting("Aimlock", &lock, lock);
}

Aimbot::~Aimbot() {
}

const char* Aimbot::getModuleName() {
	return "Aimbot";
}

struct CompareTargetEnArray {
	bool operator()(Entity* lhs, Entity* rhs) {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<Entity*> targetList137;
void findEntity713(Entity* currentEntity, bool isRegularEntity) {
	static auto aimbotMod = moduleMgr->getModule<Aimbot>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;

	if (!Game.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!Game.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 66) // Falling block
		return;

	if (currentEntity->getEntityTypeId() == 69) // XP
		return;

	if (aimbotMod->mobs) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->isPlayer())
			return;

		if (currentEntity->getAABBShapeComponent()->aabb.width <= 0.01f || currentEntity->getAABBShapeComponent()->aabb.height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;

		if (currentEntity->getEntityTypeId() == 64) // item
			return;

		if (currentEntity->getEntityTypeId() == 80) // arrow
			return;

		if (currentEntity->getEntityTypeId() == 51) // npc
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist <= aimbotMod->range)
		targetList137.push_back(currentEntity);
}

void Aimbot::onPostRender(MinecraftUIRenderContext* renderCtx) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr)
		return;
	
	targetList137.clear();
	Game.forEachEntity(findEntity713);

	if (!targetList137.empty()) {
		Vec3 origin = Game.getClientInstance()->levelRenderer->getOrigin();

		std::sort(targetList137.begin(), targetList137.end(), CompareTargetEnArray());

		Vec2 angle = origin.CalcAngle(*targetList137[0]->getPos());
		Vec2 appl = angle.sub(localPlayer->getActorHeadRotationComponent()->rot).normAngles();
		appl.x = -appl.x;
		if ((appl.x < verticalrange && appl.x > -verticalrange) && (appl.y < horizontalrange && appl.y > -horizontalrange) && GameData::canUseMoveKeys()) {
			PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
			ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (sword && !(item->getItem()->isWeapon()))
				return;

			if (click && !Game.isLeftClickDown())
				return;

			if (!lock) {
				appl.x /= (100.f - verticalspeed);
				appl.y /= (100.f - horizontalspeed);
				if (appl.x >= 1 || appl.x <= -1) appl.div(abs(appl.x));
				if (appl.y >= 1 || appl.y <= -1) appl.div(abs(appl.y));
			}
			if (!vertical)
				appl.x = 0;
			localPlayer->applyTurnDelta(&appl);
		}
	}
}
