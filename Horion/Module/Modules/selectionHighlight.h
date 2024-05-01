#pragma once
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class selectionHighlight : public IModule {
public:
	bool hurttime = false;
	int targethud = 0;
	int counter = 0;
	int range = 40.f;

	selectionHighlight();
	~selectionHighlight();

	SettingEnum mode = this;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(GameMode* gm);
	virtual void onEnable() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};