#include "Timer.h"

Timer::Timer() : IModule(0, Category::MISC, "Increase the ticks per second.") {
	registerIntSetting("TPS", &timer, timer, 0, 500);
}

Timer::~Timer() {
}

const char* Timer::getModuleName() {
	return "Timer";
}

void Timer::onTick(GameMode* gm) {
	Game.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
}

void Timer::onDisable() {
	Game.getClientInstance()->minecraft->setTimerSpeed(20.f);
}