#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class Aimbot : public IModule {
private:
	bool vertical = true;
	bool sword = false;
	bool click = false;
	float horizontalspeed = 50.f;
	float verticalspeed = 50.f;
	float verticalrange = 40.f;
	float horizontalrange = 60.f;
	bool lock = false;

public:
	float range = 4.f;
	bool mobs = false;

	Aimbot();
	~Aimbot();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};
