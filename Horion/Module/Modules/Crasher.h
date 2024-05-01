#pragma once

#include "Module.h"

class Crasher : public IModule {
public:
	Crasher();
	~Crasher();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
};
