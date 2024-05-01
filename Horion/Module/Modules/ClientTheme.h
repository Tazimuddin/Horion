#pragma once
#include "Module.h"

class ClientTheme : public IModule {
public:
	SettingEnum Theme = SettingEnum(this);
	ClientTheme();
	~ClientTheme();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	void onRender(MinecraftUIRenderContext* renderCtx);
};