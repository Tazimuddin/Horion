#include "RepairCommand.h"

RepairCommand::RepairCommand() : IMCCommand("repair", "Repairs an item", "") {
}

RepairCommand::~RepairCommand() {
}

bool RepairCommand::execute(std::vector<std::string>* args) {
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();

	auto transactionManager = Game.getLocalPlayer()->getTransactionManager();

	Inventory* inv = supplies->inventory;

	int selectedSlot = supplies->selectedHotbarSlot;

	ItemStack* item = inv->getItemStack(selectedSlot);

	if (item == nullptr || item->item == nullptr) {
		clientMessageF("Please hold an item!");
		return false;
	}

	transactionManager->addInventoryAction(InventoryAction(selectedSlot, item, nullptr, InventorySource(ContainerInventory, inventory, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(0, nullptr, item, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag)));

	item->getItem()->setDamageValue(*item, 0);

	transactionManager->addInventoryAction(InventoryAction(0, item, nullptr, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag)));
	transactionManager->addInventoryAction(InventoryAction(selectedSlot, nullptr, item, InventorySource(ContainerInventory, inventory, NoFlag)));

	inv->setItem(selectedSlot, *item);

	transactionManager->addInventoryAction(InventoryAction(selectedSlot, nullptr, item, InventorySource(ContainerInventory, inventory, NoFlag)));

	clientMessageF("Repaired item!");
	return true;
}
