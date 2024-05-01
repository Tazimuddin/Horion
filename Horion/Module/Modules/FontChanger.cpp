#include "FontChanger.h"

FontChanger::FontChanger() : IModule(0, Category::CUSTOM, "Font Changer.") {
	Fonts.addEntry(EnumEntry("Notosans", 0)).addEntry(EnumEntry("Mojangles", 1));
	registerEnumSetting("Fonts", &Fonts, 0);
}

FontChanger::~FontChanger() {
}

const char* FontChanger::getModuleName() {
	return "Font";
}