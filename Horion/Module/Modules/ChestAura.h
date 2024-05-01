#pragma once

#include "..\ModuleManager.h"
#include "Module.h"

class ChestAura : public IModule {
private:
	int range = 3;
	bool enderchests = false;

public:
	MoveInputHandler* inputHandler = nullptr;
	ChestAura();
	~ChestAura();

	std::vector<Vec3i> chestlist;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
};
