#pragma once
#include "../ModuleManager.h"
#include "Module.h"

class NoEntityRender : public IModule {
public:
	NoEntityRender();
	~NoEntityRender();

	bool isBoat = false;
	bool isMinecart = false;
	bool isFallingBlock = true;
	bool isItems = false;
	bool isPlayers = false;
	bool isXp = false;
	bool isTNT = false;
	bool isArmourStand = false;
	bool isPainting = false;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};