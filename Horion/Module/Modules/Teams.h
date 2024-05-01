#pragma once

#include "Module.h"

class Teams : public IModule {
private:
	bool alliedCheck = false;
	bool colorCheck = true;

public:
	Teams();
	~Teams();

	bool isAlliedCheckEnabled() { return isEnabled() && alliedCheck; };
	bool isColorCheckEnabled() { return isEnabled() && colorCheck; };

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
