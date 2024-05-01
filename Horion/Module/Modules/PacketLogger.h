#pragma once

#include "Module.h"

class PacketLogger : public IModule {
public:
	SettingEnum packetType;
	bool packetadd;
	bool authchunk = false;
	bool setTitle = false;
	SettingEnum addressType;
	PacketLogger();
	~PacketLogger();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onSendClientPacket(Packet* packet) override;
};