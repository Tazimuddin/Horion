#pragma once

#include "Module.h"

class Tower : public IModule {
private:
	float motion = 0.5f;
	bool tryTower(Vec3 blockBelow);

public:
	Tower();
	~Tower();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};
