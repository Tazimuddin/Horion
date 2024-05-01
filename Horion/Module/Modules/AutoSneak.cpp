#include "AutoSneak.h"

AutoSneak::AutoSneak() : IModule(0, Category::MOVEMENT, "Automatically sneak without holding the key.") {
	registerBoolSetting("Silent", &doSilent, doSilent);
}

AutoSneak::~AutoSneak() {
}

const char* AutoSneak::getModuleName() {
	return "AutoSneak";
}

void AutoSneak::onTick(GameMode* gm) {

	if (!doSilent)
		Game.getClientInstance()->getMoveTurnInput()->isSneakDown = true;
}

void AutoSneak::onDisable() {
	if (Game.getLocalPlayer() == nullptr)
		return;

	if (!doSilent) {
		Game.getClientInstance()->getMoveTurnInput()->isSneakDown = false;
		return;
	}

	PlayerActionPacket p;
	p.action = 12;  //stop crouch packet
	p.entityRuntimeId = Game.getLocalPlayer()->getRuntimeIDComponent()->runtimeID;
	Game.getClientInstance()->loopbackPacketSender->sendToServer(&p);
}

void AutoSneak::onEnable() {
	if (Game.getLocalPlayer() == nullptr)
		return; //fixed crash
	
	if (doSilent) {
		PlayerActionPacket p;
		p.action = 11;  //start crouch packet
		p.entityRuntimeId = Game.getLocalPlayer()->getRuntimeIDComponent()->runtimeID;
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&p);
	}
}
