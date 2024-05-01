#include "EditionFaker.h"

EditionFaker::EditionFaker() : IModule(0, Category::MISC, "Fakes your device.") {
	edition.addEntry(EnumEntry("Unknown", 0))
	.addEntry(EnumEntry("Android", 1))
	.addEntry(EnumEntry("iOS", 2))
	.addEntry(EnumEntry("macOS", 3))  // OS_X
	.addEntry(EnumEntry("FireOS", 4))
	.addEntry(EnumEntry("GearVR", 5))
	.addEntry(EnumEntry("Hololens", 6))
	.addEntry(EnumEntry("Win10", 7))  // Windows 10 (PC)
	.addEntry(EnumEntry("Win32", 8))  // Windows
	.addEntry(EnumEntry("Linux", 9))  // Dedicated
	.addEntry(EnumEntry("TvOS", 10))
	.addEntry(EnumEntry("Playstation", 11))      // Orbis
	.addEntry(EnumEntry("Nintendo Switch", 12))  // NX
	.addEntry(EnumEntry("Xbox", 13))
	.addEntry(EnumEntry("Windows Phone", 14));
	registerEnumSetting("Edition", &edition, 1);
}

EditionFaker::~EditionFaker() {
}

int EditionFaker::getFakedEditon() {
	return edition.GetSelectedEntry().GetValue();
}

const char* EditionFaker::getModuleName() {
	return "EditionFaker";
}
