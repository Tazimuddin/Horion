#include "FriendsManager.h"

#include <windows.storage.h>
#include <wrl.h>

using namespace ABI::Windows::Storage;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
FriendsManager friends;

FriendsManager::FriendsManager() {
}

FriendsManager::~FriendsManager() {
}

void FriendsManager::addFriendToList(const std::string& name) {
	friends.List.push_back(name);
}

std::vector<std::string> FriendsManager::getList() {
	return friends.List;
}

void FriendsManager::loadList(std::vector<std::string> List) {
	friends.List = List;
}

std::string FriendsManager::getFromList(int Friend) {
	return friends.List.at(Friend);
}

bool FriendsManager::findFriend(const std::string& name) {
	return std::find(friends.List.begin(), friends.List.end(), name) != friends.List.end();
}

bool FriendsManager::removeFriend(const std::string& g) {
	for (std::vector<std::string>::iterator it = friends.List.begin(); it != friends.List.end(); ++it) {
		std::string copy = *it;
		std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
		if (copy.find(g) != std::string::npos) {
			friends.List.erase(it);
			return true;
		}
	}
	return false;
}