#include "ChestStealer.h"
#include "../ModuleManager.h"

ChestStealer::ChestStealer() : IModule(0, Category::PLAYER, "Automatically takes all items out of a chest.") {
	registerIntSetting("Closing Delay", &setDelay, setDelay, 0, 20);
	registerBoolSetting("Enhanced", &enhanced, enhanced);
}

ChestStealer::~ChestStealer() {
}

const char* ChestStealer::getModuleName() {
	return "ChestStealer";
}

void ChestStealer::chestScreenController_tick(ChestScreenController* c) {
	if (c != nullptr && !Game.getLocalPlayer()->canOpenContainerScreen()) {
		delay++;
		std::vector<int> items = {};
		auto invcleanerMod = moduleMgr->getModule<InventoryCleaner>();
		for (int i = 0; i < 54; i++) {
			ItemStack* stack = c->_getItemStack(TextHolder("container_items"), i);
			if (stack != nullptr && stack->item != NULL)
				if (!enhanced || invcleanerMod->stackIsUseful(stack))
					items.push_back(i);
		}
		if (!items.empty() && !Game.getLocalPlayer()->getSupplies()->inventory->isFull()) {
			for (int i : items) {
				if (delay > setDelay && setDelay > 0) {
					c->handleAutoPlace("container_items", i);
					delay = 0;
				} else if (setDelay == 0)
					c->handleAutoPlace("container_items", i);
			}
		} else c->tryExit();
	}
}
