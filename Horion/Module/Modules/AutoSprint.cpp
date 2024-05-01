#include "AutoSprint.h"

AutoSprint::AutoSprint() : IModule(0, Category::MOVEMENT, "Automatically sprint without holding the key.") {
	registerBoolSetting("All Directions", &alldirections, alldirections);
}

AutoSprint::~AutoSprint() {
}

const char* AutoSprint::getModuleName() {
	return "AutoSprint";
}

void AutoSprint::onTick(GameMode* gm) {
	if (!gm->player->isSprinting() && gm->player->entityLocation->velocity.magnitudexz() > 0.01f) {
		GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
		if (alldirections || GameData::isKeyDown(*input->forwardKey))
			gm->player->setSprinting(true);
	}
}