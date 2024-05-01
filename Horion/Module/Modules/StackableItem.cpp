#include "StackableItem.h"

StackableItem::StackableItem() : IModule(0, Category::PLAYER, "Stack items you normally wouldn't be able to stack (e.g. swords).") {
	registerIntSetting("MaxItemAmount", &maxAmount, maxAmount, 1, 255);
}

StackableItem::~StackableItem() {}

const char* StackableItem::getModuleName() {
	return "StackableItem";
}

void StackableItem::onTick(GameMode* gm) {
	if (auto player = Game.getLocalPlayer(); player != nullptr) {
		if (auto inventory = player->getSupplies()->inventory; inventory != nullptr) {
			for (int i = 0; i < 36; i++) {
				if (auto stack = inventory->getItemStack(i); stack->item != nullptr) {
					auto item = *stack->item;
					item->setStackedByData(true);
					item->setMaxStackSize(maxAmount);
				}
			}
		}
	}
}