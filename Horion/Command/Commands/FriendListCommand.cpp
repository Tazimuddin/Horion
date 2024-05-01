#include "FriendListCommand.h"
#include "../../FriendList/FriendsManager.h"

FriendListCommand::FriendListCommand() : IMCCommand("friend", "Add/Remove friendly players", "<add/remove>") {
	registerAlias("friendlist");
}

FriendListCommand::~FriendListCommand() {
}

static std::vector<Entity*> targetList9;
void findEntity4(Entity* currentEntity, bool isRegularEntity) {
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

	targetList9.push_back(currentEntity);
}

bool FriendListCommand::execute(std::vector<std::string>* args) {
	targetList9.clear();
	Game.forEachEntity(findEntity4);

	if (!targetList9.empty())
		return true;

	assertTrue(args->size() >= 3);

	std::string subcommand = args->at(1);
	std::transform(subcommand.begin(), subcommand.end(), subcommand.begin(), ::tolower);

	std::string searchedName = args->at(2);
	std::transform(searchedName.begin(), searchedName.end(), searchedName.begin(), ::tolower);

	size_t listSize = targetList9.size();

	if (listSize > 10000) {
		return true;
	}

	std::string playerName;

	// Loop through all players and retrieve their information
	for (size_t i = 0; i < listSize; i++) {
		Entity* currentEntity = targetList9.at(i);

		if (currentEntity == 0) {
			break;
		}

		if (currentEntity == Game.getLocalPlayer()) {
			continue;  // Skip local player
		}

		std::string currentEntityName(currentEntity->getNameTag()->getText());
		std::transform(currentEntityName.begin(), currentEntityName.end(), currentEntityName.begin(), ::tolower);

		if (currentEntityName.find(searchedName) == std::string::npos) {
			continue;  // Continue if name not found
		}

		playerName = currentEntity->getNameTag()->getText();
		break;
	}

	if (playerName.size() <= 1) {
		clientMessageF("[%sHorion%s] %sCouldn't find player: %s!", GOLD, WHITE, RED, searchedName.c_str());
		return true;
	}

	if (subcommand == "add") {
		FriendsManager::addFriendToList(playerName);
		clientMessageF("[%sHorion%s] %s%s is now your friend!", GOLD, WHITE, GREEN, playerName.c_str());
		return true;
	} else if (subcommand == "remove") {
		if (FriendsManager::removeFriend(searchedName)) {
			clientMessageF("[%sHorion%s] %s%s has been removed from your friend list!", GOLD, WHITE, GREEN, searchedName.c_str());
		} else {
			clientMessageF("[%sHorion%s] %s%s was not in your friend list!", GOLD, WHITE, GREEN, searchedName.c_str());
		}
		return true;
	}

	return true;
}