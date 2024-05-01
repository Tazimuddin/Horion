#pragma once

#include "Module.h"

class AutoGapple : public IModule {
private:
	int health;
	int stackSize = 0;
	int lastSlot = 0;
	int lastHealth = -1;
	int wait = 0;

public:
	MoveInputHandler* inputHandler = nullptr;
	AutoGapple();
	~AutoGapple();

	int findGapple();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
};
