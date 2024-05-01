#include "PlayerTeleportCommand.h"
#include "../../../Utils/Utils.h"
#include "../../Module/Modules/Blink.h"
#include "../../Module/Modules/Timer.h"

PlayerTeleportCommand::PlayerTeleportCommand() : IMCCommand("playertp", "Teleports to players coordinates", "<NameOfThePlayer>") {
}

PlayerTeleportCommand::~PlayerTeleportCommand() {
}


static std::vector<Entity*> targetList8;
void findEntity3(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;

	if (!Game.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (!currentEntity->isPlayer())
		return;

	targetList8.push_back(currentEntity);
}

bool PlayerTeleportCommand::execute(std::vector<std::string>* args) {
	targetList8.clear();
	Game.forEachEntity(findEntity3);

	if (targetList8.empty())
		return true;

	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() > 1);  // .playertp <player>
	std::string nameOfPlayer = args->at(1);
	assertTrue(!nameOfPlayer.empty());
	std::string nameOfPlayerLower = nameOfPlayer;
	std::transform(nameOfPlayerLower.begin(), nameOfPlayerLower.end(), nameOfPlayerLower.begin(), ::tolower);
	nameOfPlayerLower = Utils::sanitize(nameOfPlayerLower);

	size_t listSize = targetList8.size();
	Vec3 pos;

	if (listSize > 5000) {
		return true;
	}

	std::string playerName;

	// Loop through all the players and retrieve their information
	for (size_t i = 0; i < listSize; i++) {
		Entity* currentEntity = targetList8.at(i);

		if (currentEntity == nullptr)
			break;

		if (currentEntity == Game.getLocalPlayer())  // Skip local player
			continue;

		if (currentEntity->getNameTag() == nullptr)
			continue;

		std::string name(currentEntity->getNameTag()->getText());

		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (name.find(nameOfPlayerLower) == std::string::npos)
			continue;

		pos = *currentEntity->getPos();
		playerName = currentEntity->getNameTag()->getText();
		break;
	}

	if (pos.iszero()) {
		clientMessageF("[%sHorion%s] %sCouldn't find player: %s!", GOLD, WHITE, RED, nameOfPlayer.c_str());
		return true;
	}

	Game.getLocalPlayer()->setPos(pos);
	clientMessageF("[%sHorion%s] %sTeleported to %s", GOLD, WHITE, GREEN, playerName.c_str());
	return true;
}
