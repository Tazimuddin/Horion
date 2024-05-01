#include "AntiVoid.h"

AntiVoid::AntiVoid() : IModule(0, Category::MOVEMENT, "Automatically teleports you back up if you fall down more than X blocks.") {
	registerIntSetting("Distance", &distance, distance, 1, 20);
}

AntiVoid::~AntiVoid() {
}

const char* AntiVoid::getModuleName() {
	return "AntiVoid";
}

void AntiVoid::onTick(GameMode* gm) {
	LocalPlayer* player = Game.getLocalPlayer();
	Vec3 blockBelow = *player->getPos();
	blockBelow.y -= player->getAABBShapeComponent()->aabb.height;
	blockBelow.y -= 0.5f;

	if (player->getRegion()->getBlock(blockBelow)->blockLegacy->blockId != 0 && ((player->region->getBlock(blockBelow)->blockLegacy))->material->isSolid) {
		savepos = blockBelow;
		savepos.y += player->getAABBShapeComponent()->aabb.height;
		savepos.y += 0.5f;
	}

	if (player->getFallDistanceComponent()->fallDistance >= distance) {
		player->setPos(savepos);
	}
}
