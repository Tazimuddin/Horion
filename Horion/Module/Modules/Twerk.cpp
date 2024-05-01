#include "Twerk.h"

Twerk::Twerk() : IModule(0x0, Category::MOVEMENT, "Crouch Spam.") {
	registerFloatSetting("Delay", &delay, delay, 0.05f, 10);
}

Twerk::~Twerk() {
}

const char* Twerk::getModuleName() {
	return "Twerk";
}

void Twerk::onTick(GameMode* gm) {
	Odelay++;
	if (Odelay > delay * *Game.getClientInstance()->minecraft->timer) {
		Game.getClientInstance()->getMoveTurnInput()->isSneakDown = !Game.getClientInstance()->getMoveTurnInput()->isSneakDown;
		Odelay = 0;
	}
}