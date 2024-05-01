#include "AntiInvis.h"

AntiInvis::AntiInvis() : IModule(0, Category::VISUAL, "See entities with invisibility potion") { }

AntiInvis::~AntiInvis() { }

const char* AntiInvis::getModuleName() {
	return "AntiInvis";
}
