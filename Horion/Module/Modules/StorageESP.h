#pragma once

#include "Module.h"

class StorageESP : public IModule {
private:
	std::vector<AABB> bufferedChestList;
	float opacity = 1.f;
	std::mutex listLock;
	SettingEnum mode{this};
	bool fill = false;

public:
	StorageESP();
	~StorageESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onTick(GameMode* gm) override;
	virtual void onLevelRender() override;
};
