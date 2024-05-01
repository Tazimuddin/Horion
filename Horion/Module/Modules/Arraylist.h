#pragma once

#include "..\ModuleManager.h"
#include "Module.h"

class Arraylist : public IModule {

public:
	bool clickToggle = true;
	float cycleSpeed = 2.f;
	float saturation = 0.5f;
	float alpha = 1.f;

	// I will make do this another time
	SettingEnum style = SettingEnum(this);

	Arraylist();
	~Arraylist();

	// Inherited via IModule
	virtual const char* getModuleName();
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx);
};
