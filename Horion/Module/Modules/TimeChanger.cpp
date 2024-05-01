#include "TimeChanger.h"

TimeChanger::TimeChanger() : IModule(0, Category::VISUAL, "Changes the clientside time.") {
	registerFloatSetting("Modifier", &modifier, modifier, 0.1f, 1.f);
}

TimeChanger::~TimeChanger() {
}

const char* TimeChanger::getModuleName() {
	return "TimeChanger";
}
