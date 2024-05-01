#include "Spammer.h"
#include "../../../Utils/Utils.h"

Spammer::Spammer() : IModule(0, Category::MISC, "Spams a message in a specified delay.") {
	registerIntSetting("Delay", &delay, delay, 1, 10);
	registerIntSetting("Length", &length, length, 1, 60);
	registerBoolSetting("Bypass", &bypass, bypass);
}

Spammer::~Spammer() {
}

const char* Spammer::getModuleName() {
	return "Spammer";
}

void Spammer::onTick(GameMode* gm) {
	Odelay++;
	if (Odelay > delay * 20) {
		TextPacket textPacket;
		textPacket.message.setText(bypass ? (message + " | " + Utils::randomString(length)) : message);
		textPacket.sourceName.setText(Game.getLocalPlayer()->getNameTag()->getText());
		textPacket.xboxUserId = std::to_string(Game.getLocalPlayer()->getUserId());
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
		Odelay = 0;
	}
}
