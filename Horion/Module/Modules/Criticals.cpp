#include "Criticals.h"

Criticals::Criticals() : IModule(0, Category::COMBAT, "Use When you do HvH it given nofall and good criticals ( make sure when you toch ground don't move on land.") {
	registerBoolSetting("LifeBoat", &LB, LB);
}

Criticals::~Criticals() {
}

const char* Criticals::getModuleName() {
	return ("Criticals");
}

void Criticals::onTick(GameMode* gm) {
}

void Criticals::onTick(Packet* gm) {
	if (LB) {
		LocalPlayer* player = Game.getLocalPlayer();
		Vec3 pos = *player->getPos();
		pos.y += 0.2f;
		MovePlayerPacket movePlayerPacket;
		movePlayerPacket.onGround = false;
		movePlayerPacket = MovePlayerPacket(player, pos);
		PlayerAuthInputPacket authInputPacket;
		authInputPacket = PlayerAuthInputPacket(pos, player->getActorHeadRotationComponent()->rot.x, player->getActorHeadRotationComponent()->rot.y, player->getActorRotationComponent()->rot.y);
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&movePlayerPacket);
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&authInputPacket);
	}
}

void Criticals::onSendPacket(Packet* packet) {
	LocalPlayer* player = Game.getLocalPlayer();
	if (player != nullptr) {
		Vec3 pos = *player->getPos();
		pos.y += 0.2f;
		if (packet->isInstanceOf<MovePlayerPacket>() && player != nullptr) {
			MovePlayerPacket* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
			movePacket->onGround = false;
			movePacket->Position = pos;
		}
		if (packet->isInstanceOf<PlayerAuthInputPacket>() && player != nullptr) {
			PlayerAuthInputPacket* authInput = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			authInput->pos = pos;
		}
	}
}