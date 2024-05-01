#include "Phase.h"

Phase::Phase() : IModule(0x0, Category::MOVEMENT, "Walk straight through walls.") {}

Phase::~Phase() {}

const char* Phase::getModuleName() {
	return "Phase";
}

void Phase::onTick(GameMode* gm) {
	gm->player->getAABBShapeComponent()->aabb.upper.y = gm->player->getAABBShapeComponent()->aabb.lower.y;
}

void Phase::onDisable() {
	if (Game.getLocalPlayer() != nullptr)
		Game.getLocalPlayer()->getAABBShapeComponent()->aabb.upper.y += 1.8f;
}
