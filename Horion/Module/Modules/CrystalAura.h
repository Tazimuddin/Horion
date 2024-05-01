#pragma once

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "Module.h"

class CrystalAura : public IModule {
private:
	int prevSlot;
	int delay = 0;
	int eRange = 3;
	bool autoplace = true;
	bool pEnhanced = true;
	bool dEnhanced = true;
	bool Preview = true;
	bool AutoSelect = true;
	bool FinishSelect = false;
	PlayerInventoryProxy* supplies = nullptr;
	Inventory* inv = nullptr;

public:
	CrystalAura();
	~CrystalAura();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onEnable() override;
	virtual void onDisable() override;

	int cRange = 10;
	int pRange = 5;
	int range = 10;

	void CPlace(GameMode* gm, Vec3* pos);
	void DestroyC(Entity* ent, int range);
};