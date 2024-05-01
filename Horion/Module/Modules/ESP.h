#pragma once
#include "../../../SDK/Camera.h"
#include "../../../Utils/Target.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"
#include "Module.h"

class ESP : public IModule {
public:
	bool tracers = false;
	bool mobs = false;
	bool is2D = false;
	int plrR = 255;
	bool itemESP = false;
	int plrG = 0;
	int plrB = 0;
	bool doRainbow = true;

	SettingEnum mode = this;

	void onLevelRender() override;
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	ESP();
};