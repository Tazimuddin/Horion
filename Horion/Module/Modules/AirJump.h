#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class AirJump : public IModule {
private:
	int hasJumped = 0;
	bool legacyMode = false;
	int tick = 0;
	int tickTimer = 0;

public:
	AirJump();
	~AirJump();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
