#include "Nuker.h"

Nuker::Nuker() : IModule(VK_NUMPAD5, Category::WORLD, "Break multiple blocks at once.") {
	registerIntSetting("Radius", &nukerRadius, nukerRadius, 1, 10);
	registerBoolSetting("Veinminer", &veinMiner, veinMiner);
	registerBoolSetting("Autodestroy", &autodestroy, autodestroy);
}

Nuker::~Nuker() {
}

const char* Nuker::getModuleName() {
	return "Nuker";
}

void Nuker::onTick(GameMode* gm) {
	if (!autodestroy) return;
	Vec3i tempPos = *gm->player->getPos();
	for (int x = -nukerRadius; x < nukerRadius; x++) {
		for (int y = -nukerRadius; y < nukerRadius; y++) {
			for (int z = -nukerRadius; z < nukerRadius; z++) {
				tempPos.x = (int)gm->player->getPos()->x + x;
				tempPos.y = (int)gm->player->getPos()->y + y;
				tempPos.z = (int)gm->player->getPos()->z + z;
				if (tempPos.y > -64 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isSolid) {
					gm->destroyBlock(&tempPos, 1);
				}
			}
		}
	}
}
