#include "InventoryTransaction.h"

#include "../Utils/Utils.h"
void InventoryTransactionManager::addInventoryAction(const InventoryAction& action, bool forceBalanced) {
	static auto InventoryTransactionManager__addAction = Utils::FindSignature("48 89 5C ? ? 55 56 57 41 56 41 57 48 83 EC ? 45 0F B6 ? 4C 8B F2 48 8B F9");
	if (InventoryTransactionManager__addAction)
		reinterpret_cast<void(__fastcall*)(InventoryTransactionManager*, const InventoryAction&, bool)>(InventoryTransactionManager__addAction)(this, action, forceBalanced);
}

void InventoryAction::fixInventoryStuff(ItemDescriptor* a1, ItemStack* a2) {
	// Fairly certain this is NetworkItemStackDescriptor::NetworkItemStackDescriptor(ItemStack const &)
	// ??0NetworkItemStackDescriptor@@QEAA@AEBVItemStack@@@Z
	static auto fixInvStuff = Utils::FindSignature("48 89 5C ? ? 48 89 6C ? ? 56 57 41 56 48 81 EC B0 ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 ? ? ? ? ? 48 8B EA 48 8B F9");
	if (fixInvStuff)
		reinterpret_cast<void(__fastcall*)(ItemDescriptor*, ItemStack*)>(fixInvStuff)(a1, a2);
}