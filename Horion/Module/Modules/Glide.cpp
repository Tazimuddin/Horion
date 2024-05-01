#include "Glide.h"

Glide::Glide() : IModule(0, Category::MOVEMENT, "Float down like a chicken.") {
	registerFloatSetting("Value", &glideMod, glideMod, -2, 1);
}

Glide::~Glide() {}

const char* Glide::getModuleName() {
	if (isEnabled()) {
		static char modName[30];
		snprintf(modName, 30, "Glide [%.2f]", glideModEffective);
		return modName;
	}
	return "Glide";
}

void Glide::onTick(GameMode* gm) {
	glideModEffective = glideMod;
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();

	if (Game.canUseMoveKeys()) {
		if (GameData::isKeyDown(*input->spaceBarKey))
			glideModEffective += 0.2f;
		if (GameData::isKeyDown(*input->sneakKey))
			glideModEffective -= 0.2f;
	}
	gm->player->entityLocation->velocity.y = glideModEffective;
}

const char* Glide::getRawModuleName() {
	return "Glide";
}