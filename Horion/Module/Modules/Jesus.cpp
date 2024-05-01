#include "Jesus.h"

Jesus::Jesus() : IModule(0, Category::MOVEMENT, "Walk over water, like Jesus.") {
}

Jesus::~Jesus() {
}

const char* Jesus::getModuleName() {
	return "Jesus";
}

void Jesus::onTick(GameMode* gm) {
	if (gm->player->isSneaking()) return;

	if (gm->player->isInWater()) {
		gm->player->entityLocation->velocity.y = 0.06f;
		gm->player->setOnGround(true);
		wasInWater = true;
	} else if (gm->player->isInWater()) {
		gm->player->entityLocation->velocity.y = 0.1f;
		gm->player->setOnGround(true);
		wasInWater = true;
	} else {
		if (wasInWater) {
			wasInWater = false;
			gm->player->entityLocation->velocity.x *= 1.2f;
			gm->player->entityLocation->velocity.x *= 1.2f;
		}
	}
}
