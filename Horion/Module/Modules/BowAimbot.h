#pragma once

#include "Module.h"

class BowAimbot : public IModule {
private:
	bool silent = true;
	bool predict = false;
	bool visualize = false;
	Vec2 angle;

public:
	BowAimbot();
	~BowAimbot();

	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onSendPacket(Packet* packet) override;

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
