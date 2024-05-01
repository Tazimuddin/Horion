#include "AutoTotem.h"

AutoTotem::AutoTotem() : IModule(0, Category::PLAYER, "Automatically puts totems into your offhand.") {
}

AutoTotem::~AutoTotem() {
}

const char* AutoTotem::getModuleName() {
	return "AutoTotem";
}

void AutoTotem::onTick(GameMode* gm) {
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	InventoryTransactionManager* manager = Game.getLocalPlayer()->getTransactionManager();
	ItemStack* current = Game.getLocalPlayer()->getEquippedTotem();
	if (current->item == NULL) {
		for (int i = 0; i < 36; i++) {
			ItemStack* totem = inv->getItemStack(i);
			if (totem->item != NULL && (*totem->item)->itemId == 568) {
				InventoryAction first(i, totem, nullptr, InventorySource(ContainerInventory, inventory, NoFlag));
				InventoryAction second(37, nullptr, totem, InventorySource(ContainerInventory, inventory, NoFlag));
				Game.getLocalPlayer()->setOffhandSlot(totem);
				manager->addInventoryAction(first);
				manager->addInventoryAction(second);
			}
		}
	}	
}