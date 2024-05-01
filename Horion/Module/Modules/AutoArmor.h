#pragma once

#include "Module.h"

class AutoArmor : public IModule {
public:
	CraftingScreenController* inventoryScreen = nullptr;
	AutoArmor();
	~AutoArmor();

	// Inherited via IModule
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName() override;
};
