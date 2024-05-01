#include "SetLoreCommand.h"

SetLoreCommand::SetLoreCommand() : IMCCommand("setlore", "Sets the lore of an item", "<lore>") {
}

SetLoreCommand::~SetLoreCommand() {
}

bool SetLoreCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() >= 2);

	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	auto transactionManager = Game.getLocalPlayer()->getTransactionManager();
	Inventory* inv = supplies->inventory;
	int selectedSlot = supplies->selectedHotbarSlot;
	ItemStack* item = inv->getItemStack(selectedSlot);

	if (item == nullptr || item->item == nullptr) {
		clientMessageF("Please hold an item!");
		return false;
	}

	std::string lore;

	for (int i = 1; i < args->size(); i++) {
		lore += args->at(i);
		if (i < args->size() - 1) {
			lore += " ";
		}
	}

	transactionManager->addInventoryAction(InventoryAction(selectedSlot, item, nullptr, InventorySource(ContainerInventory, inventory, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(0, nullptr, item, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag)));

	item->setLore(lore);

	transactionManager->addInventoryAction(InventoryAction(0, item, nullptr, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(selectedSlot, nullptr, item, InventorySource(ContainerInventory, inventory, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(selectedSlot, nullptr, item, InventorySource(ContainerInventory, inventory, NoFlag)));

	clientMessageF("Set lore to \"%s\"!", lore.c_str());
	return true;
}