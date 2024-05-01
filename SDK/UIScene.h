#pragma once

#include "TextHolder.h"
#include "../Utils/Utils.h"

class UIScene {
public:
	bool isPlayScreen() {
		return Utils::CallVFunc<55, bool>(this);
	}

	void getScreenName(TextHolder* txt) {
		Utils::CallVFunc<68, void, TextHolder*>(this, txt);
	}
};
