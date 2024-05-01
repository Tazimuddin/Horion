#include "Tracer.h"

#include "../../../SDK/Camera.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

bool old = false;
Tracer::Tracer() : IModule('R', Category::VISUAL, "Draws lines to ESP highlighted entities.") {
	registerBoolSetting("3D Tracers", &old, old);
}

Tracer::~Tracer() {
}

const char* Tracer::getModuleName() {
	return "Tracer";
}

void Tracer::onLevelRender() {
	if (old) {
		if (!Game.getLocalPlayer()) return;
		float calcYaw = (Game.getLocalPlayer()->getActorRotationComponent()->rot.y + 90) * (PI / 180);
		float calcPitch = (Game.getLocalPlayer()->getActorRotationComponent()->rot.x) * -(PI / 180);
		Vec3 moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * 0.5f;
		moveVec.y = sin(calcPitch) * 0.5f;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * 0.5f;

		const Vec3 origin = Game.getClientInstance()->levelRenderer->getOrigin().add(moveVec); /*place the start of the line slightly forward so it won't get clipped*/
		Game.forEachEntity([&](Entity* ent, bool valid) {
			if (Target::isValidTarget(ent) && Game.canUseMoveKeys()) {
				DrawUtils::setColor(255, 255, 255, 1);
				DrawUtils::drawLine3d(origin, *ent->getPos(), true);
			}
		});
	}
}
std::shared_ptr<glmatrixf> refdef2;
void Tracer::onPreRender(MinecraftUIRenderContext* renderCtx) {
	glmatrixf* badrefdef = Game.getClientInstance()->getRefDef();
	refdef2 = std::shared_ptr<glmatrixf>(badrefdef->correct());

	if (!old) {
		Game.forEachEntity([&](Entity* ent, bool valid) {
			if (ent != Game.getLocalPlayer() && Target::isValidTarget(ent) && Game.canUseMoveKeys()) {
				static auto tracerMod = moduleMgr->getModule<Tracer>();
				Vec2 target;
				Vec2 screenSize;
				screenSize.x = Game.getGuiData()->widthGame;
				screenSize.y = Game.getGuiData()->heightGame;
				refdef2->OWorldToScreen(Game.getClientInstance()->levelRenderer->getOrigin(), ent->getRenderPositionComponent()->renderPos, target, Game.getClientInstance()->getFov(), screenSize);
				Vec2 mid(((Game.getClientInstance()->getGuiData()->widthGame) / 2), ((Game.getClientInstance()->getGuiData()->heightGame) / 2));
				if (target != Vec2(0, 0)) {
					DrawUtils::setColor(255, 255, 255, 1);
					DrawUtils::drawLine(mid, target, 0.2f);
				}
			}
		});
	}
}