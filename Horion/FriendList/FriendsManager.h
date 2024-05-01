#pragma once
#pragma comment(lib, "runtimeobject")
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "../../Utils/Json.hpp"

using json = nlohmann::json;

class FriendsManager {
private:
	std::vector<std::string> List;
	std::string currentFriends = "Friends";

public:
	static std::vector<std::string> getList();
	static bool findFriend(const std::string& name);
	static bool findFriend(const char* name) {
		std::string local(name);
		return findFriend(local);
	}
	static void addFriendToList(const std::string& name);
	static std::string getFromList(int Friend);
	static bool removeFriend(const std::string& g);
	static void loadList(std::vector<std::string> list);
	FriendsManager();
	~FriendsManager();
};

extern FriendsManager friends;