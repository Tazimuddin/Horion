#pragma once

#include "Module.h"

class AirSwim : public IModule {
public:
	AirSwim();
	~AirSwim();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
};