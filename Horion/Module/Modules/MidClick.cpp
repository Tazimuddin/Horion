#include "MidClick.h"
#include "../../FriendList/FriendsManager.h"

MidClick::MidClick() : IModule(0, Category::PLAYER, "Click a player with [ Right Click ] to add em as a friend.") {
}

MidClick::~MidClick() {
}

const char* MidClick::getModuleName() {
	return "MidClick";
}

void MidClick::onTick(GameMode* gm) {
	Entity* entity = Game.getLocalPlayer()->level->getEntity();
	if (entity == nullptr) 
		return;

	std::string name = entity->getNameTag()->getText();

	if (GameData::isRightClickDown () && !hasClicked) {
		if (!FriendsManager::findFriend(name)) {
			FriendsManager::addFriendToList(name);
			Game.getGuiData()->displayClientMessageF("%sSuccessfully added %s %sto your friendlist.", GREEN, name.c_str(), GREEN);
		} else {
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			FriendsManager::removeFriend(name);
			Game.getGuiData()->displayClientMessageF("%sSuccessfully removed %s %sfrom your friendlist.", GREEN, name.c_str(), GREEN);
		}
		hasClicked = true;
	} else if (!GameData::isWheelDown()) {
		hasClicked = false;
	}
}
