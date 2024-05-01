#include "Partner.h"
#include "../../../SDK/Tag.h"

Partner::Partner() : IModule(0x0, Category::GUI, "Select color") {
	registerEnumSetting("Color Types", &Partnered, 0);
	Partnered = (*new SettingEnum(this))
					.addEntry(EnumEntry("Purple", 0))
					.addEntry(EnumEntry("Blue", 1))
					.addEntry(EnumEntry("Matrix", 2));
}
Partner::~Partner() {
}
const char* Partner::getModuleName() {
	return "ClientColors";
}