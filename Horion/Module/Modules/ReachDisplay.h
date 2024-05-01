#pragma once

#include <stdlib.h>

#include "Module.h"

class ReachDisplay : public IModule {
private:
	float scale = 1.0f;

	float currReach = 0.0f;
	int ticks = 0;

	char* reachStr = nullptr;

public:
	ReachDisplay();
	~ReachDisplay();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onDisable() override;
};
