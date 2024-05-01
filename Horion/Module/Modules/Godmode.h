#pragma once

#include "Module.h"

class Godmode : public IModule {
private:
	int regendelay = 5;
	int regenvalue = 5;
	int delay = 0;

public:
	Godmode();
	~Godmode();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onSendPacket(Packet* p) override;
};
