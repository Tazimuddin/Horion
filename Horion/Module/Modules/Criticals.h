#pragma once

#include "Module.h"

class Criticals : public IModule {
public:
	bool autoweapon = false;
	bool LB = true;
	Criticals();
	~Criticals();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	void onSendPacket(Packet* packet);
	void onTick(Packet* gm);
};