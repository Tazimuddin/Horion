#include "RenameCommand.h"

RenameCommand::RenameCommand() : IMCCommand("rename", "Renames an item", "<name>") {
}

RenameCommand::~RenameCommand() {
}

bool RenameCommand::execute(std::vector<std::string>* args) {
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

	std::string name;

	for (int i = 1; i < args->size(); i++) {
		name += args->at(i) + " ";
	}

	transactionManager->addInventoryAction(InventoryAction(selectedSlot, item, nullptr, InventorySource(ContainerInventory, inventory, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(0, nullptr, item, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag)));

	item->setName(name);

	transactionManager->addInventoryAction(InventoryAction(0, item, nullptr, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(selectedSlot, nullptr, item, InventorySource(ContainerInventory, inventory, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(selectedSlot, nullptr, item, InventorySource(ContainerInventory, inventory, NoFlag)));

	clientMessageF("Set name to '%s'!", name);
	return true;
}
