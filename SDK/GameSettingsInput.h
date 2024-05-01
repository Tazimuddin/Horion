#pragma once

#include "../Utils/Utils.h"

class GameSettingsInput {
public:
	BUILD_ACCESS(this, int*, attackKey, 0x20);
	BUILD_ACCESS(this, int*, pickItemKey, 0x60);
	BUILD_ACCESS(this, int*, useKey, 0xA0);
	BUILD_ACCESS(this, int*, dropKey, 0xE0);
	BUILD_ACCESS(this, int*, hotbar1Key, 0x120);
	BUILD_ACCESS(this, int*, hotbar2Key, 0x160);
	BUILD_ACCESS(this, int*, hotbar3Key, 0x1A0);
	BUILD_ACCESS(this, int*, hotbar4Key, 0x1E0);
	BUILD_ACCESS(this, int*, hotbar5Key, 0x220);
	BUILD_ACCESS(this, int*, hotbar6Key, 0x260);
	BUILD_ACCESS(this, int*, hotbar7Key, 0x2A0);
	BUILD_ACCESS(this, int*, hotbar8Key, 0x2E0);
	BUILD_ACCESS(this, int*, hotbar9Key, 0x320);
	BUILD_ACCESS(this, int*, inventoryKey, 0x360);
	BUILD_ACCESS(this, int*, togglePerspectiveKey, 0x3A0);
	BUILD_ACCESS(this, int*, spaceBarKey, 0x3E0);
	BUILD_ACCESS(this, int*, sneakKey, 0x420);
	BUILD_ACCESS(this, int*, sprintKey, 0x460);
	BUILD_ACCESS(this, int*, leftKey, 0x4A0);
	BUILD_ACCESS(this, int*, rightKey, 0x4E0);
	BUILD_ACCESS(this, int*, backKey, 0x520);
	BUILD_ACCESS(this, int*, forwardKey, 0x560);
	BUILD_ACCESS(this, int*, mobEffectsKey, 0x5A0);
	BUILD_ACCESS(this, int*, chatKey, 0x5E0);
	BUILD_ACCESS(this, int*, commandKey, 0x620);
	BUILD_ACCESS(this, int*, emoteKey, 0x660);
	BUILD_ACCESS(this, int*, menuTabLeftKey, 0x6A0);
	BUILD_ACCESS(this, int*, menuTabRightKey, 0x6E0);
	BUILD_ACCESS(this, int*, copyCoordinatesKey, 0x720);
	BUILD_ACCESS(this, int*, copyFacingCoordinatesKey, 0x760);
};
