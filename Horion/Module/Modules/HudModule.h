#pragma once

#include "Module.h"

class HudModule : public IModule {
public:
	HudModule();
	~HudModule();

	bool tabgui = false;
	bool arraylist = true;
	bool clickToggle = false;
	bool watermark = true;
	bool coordinates = false;
	bool keybinds = false;
	bool displayArmor = true;
	bool keystrokes = false;
	bool fps = false;
	bool cps = false;
	bool rgb = false;
	bool bottom = false;
	bool alwaysShow = false;

	float scale = 1.f;

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	static void drawKeystroke(char key, const Vec2& pos);
	static void drawMouseKeystroke(Vec2 pos, std::string keyString);
};