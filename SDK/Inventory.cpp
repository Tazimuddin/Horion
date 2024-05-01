#include "Inventory.h"

#include "../Memory/GameData.h"
#include "../Utils/Utils.h"
void Inventory::dropSlot(int slot) {
	// FillingContainer::dropSlot
	using drop_t = void(__fastcall*)(Inventory*, int, char);
	static drop_t func = reinterpret_cast<drop_t>(FindSignature("85 D2 0F 88 ?? ?? ?? ?? 48 89 5C 24 ?? 55 56 57 41 54"));
	if (func != 0)
		func(this, slot, 0);
}
void Inventory::dropAll() {
	// FillingContainer::dropAll will redo when needed
	//using dropAll_t = void(__fastcall*)(Inventory*, int, int, char);
	//static dropAll_t func = reinterpret_cast<dropAll_t>(FindSignature("48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 48 89 7C 24 ?? 41 56 48 83 EC ?? 48 8B 01 41 0F"));
	//if (func != 0)
	//func(this, slot, 0, 0);
	for (int i = 0; i < 36; i++) {
		dropSlot(i);
	}
}

bool Inventory::isFull() {
	int fullslots = 0;
	for (int i = 0; i < 36; i++) {
		if (this->getItemStack(i)->item != nullptr)
			fullslots++;
		if (fullslots == 36) return true;
	}
	return false;
}

void ContainerScreenController::handleAutoPlace(std::string name, int slot) {
	using ContainerScreenController__autoPlace = __int64(__stdcall*)(ContainerScreenController*, uintptr_t, TextHolder, int);
	static ContainerScreenController__autoPlace autoPlaceFunc = reinterpret_cast<ContainerScreenController__autoPlace>(FindSignature("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 8B E1 4D 8B F0"));

	TextHolder txt = TextHolder(name);

	if (autoPlaceFunc != 0x0)
		autoPlaceFunc(this, 0x7FFFFFFF, txt, slot);
}

void Inventory::moveItem(int from, int to) {
	InventoryTransactionManager* manager = Game.getLocalPlayer()->getTransactionManager();

	ItemStack emptyItemStack;
	memset(&emptyItemStack, 0, sizeof(ItemStack));


	if (to < 0) {
		to = getFirstEmptySlot();
	}

	ItemStack* item1 = getItemStack(from);
	ItemStack* item2 = getItemStack(to);

	if (!item1 || !item1->item) {
		return;
	}

	if (!item2 || !item2->item) {
		InventoryAction first(from, item1, nullptr);
		InventoryAction second(to, nullptr, item1);
		manager->addInventoryAction(first);
		manager->addInventoryAction(second);
		*item2 = *item1;
		*item1 = emptyItemStack;
	} else {
		InventoryAction first(from, item1, nullptr);
		InventoryAction second(to, item2, item1);
		InventoryAction third(from, nullptr, item2);
		manager->addInventoryAction(first);
		manager->addInventoryAction(second);
		manager->addInventoryAction(third);
		ItemStack a = *item2;
		*item2 = *item1;
		*item1 = a;
	}
}

void Inventory::swapSlots(int from, int to) {
	InventoryTransactionManager* manager = Game.getLocalPlayer()->getTransactionManager();
	ItemStack* i1 = getItemStack(from);
	ItemStack* i2 = getItemStack(to);
	InventoryAction first(from, i1, nullptr);
	InventoryAction second(to, i2, i1);
	InventoryAction third(from, nullptr, i2);
	manager->addInventoryAction(first);
	manager->addInventoryAction(second);
	manager->addInventoryAction(third);
}