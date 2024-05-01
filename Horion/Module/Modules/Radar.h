#pragma once

#include "Module.h"
#include "../../DrawUtils.h"

class Radar : public IModule {
public:
	Radar();
	~Radar();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};
