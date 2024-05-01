#pragma once
#include "ICommand.h"
class TeleportCommand : public IMCCommand {
public:
	TeleportCommand();
	~TeleportCommand();
	void onTick(GameMode* gm);
	std::vector<MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
	inline std::vector<MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};