#include "AirJump.h"

AirJump::AirJump() : IModule('G', Category::MOVEMENT, "Active Fly before teleport") {
	registerBoolSetting("Legacy", &legacyMode, legacyMode);
}

AirJump::~AirJump() {
}

const char* AirJump::getModuleName() {
	return "AirJump";
}

void AirJump::onTick(GameMode* gm) {
	if (legacyMode) {
		gm->player->setOnGround(true);
		return;
	}
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	int bps = Game.getLocalPlayer()->getBlocksPerSecond();
	if (input == nullptr)
		return;

	if (GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0) {
		tick++;
		if (tick >= tickTimer) {
			gm->player->setOnGround(true);
			gm->player->jumpFromGround();
			tick = 0;
		}
		gm->player->setOnGround(true);
		hasJumped = 0.0001;
	} else if (!GameData::isKeyDown(*input->spaceBarKey)) {
		tick++;
		if (tick >= tickTimer) {
			gm->player->setOnGround(true);
			gm->player->jumpFromGround();
			tick = 0;
		}
		hasJumped = 0;
	}

}
