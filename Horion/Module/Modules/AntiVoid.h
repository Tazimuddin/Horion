#pragma once

#include "..\ModuleManager.h"
#include "Module.h"

class AntiVoid : public IModule {
private:
	int distance = 5;
	Vec3 savepos;

public:
	MoveInputHandler* inputHandler = nullptr;
	AntiVoid();
	~AntiVoid();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
