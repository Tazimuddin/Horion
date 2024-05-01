#include "SeedCommand.h"

SeedCommand::SeedCommand() : IMCCommand("seed", "Shows you the seed of the world", "") {
}

SeedCommand::~SeedCommand() {
}

bool SeedCommand::execute(std::vector<std::string>* args) {
	if (Game.getLocalPlayer() == nullptr) return true;

	LocalPlayer* localPlayer = Game.getLocalPlayer();

	if (localPlayer->level == nullptr) return true;

	int seed = Utils::CallVFunc<109, int>(localPlayer->level);

	clientMessageF("%sSeed: %s%i", GREEN, GRAY, seed);

	return true;
}
