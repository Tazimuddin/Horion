#include "Step.h"

Step::Step() : IModule(0, Category::MOVEMENT, "Increases your step height.") {
	registerFloatSetting("Height", &height, height, 1.f, 10.f);
}

Step::~Step() {
}

const char* Step::getModuleName() {
	return "Step";
}

void Step::onTick(GameMode* gm) {
	gm->player->getMaxAutoStepComponent()->stepHeight = height;
}
void Step::onDisable() {
	if (Game.getLocalPlayer() != nullptr)
		Game.getLocalPlayer()->getMaxAutoStepComponent()->stepHeight = 0.563f;
}
