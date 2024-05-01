#include "ComplexInventoryTransaction.h"
#include "../Utils/Utils.h"
ComplexInventoryTransaction::ComplexInventoryTransaction(InventoryTransaction& transac) {
	static uintptr_t** ComplexInventoryTransactionVtable = 0x0;
	if (ComplexInventoryTransactionVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("4C 8D 3D ? ? ? ? 4C 89 7D ? E8 ? ? ? ? 48 89 45 ? 89 75");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		ComplexInventoryTransactionVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (ComplexInventoryTransactionVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ComplexInventoryTransaction));  // Avoid overwriting vtable
	vTable = ComplexInventoryTransactionVtable;
	uintptr_t boi = reinterpret_cast<uintptr_t>(this);
	using constructor_t = void(__fastcall*)(uintptr_t, InventoryTransaction&);
	static constructor_t constructor = reinterpret_cast<constructor_t>(FindSignature("48 89 5C ? ? 89 54 24 ? 55 56 57 41 56 41 57 48 8B EC"));
	if (constructor != 0)
		constructor(boi + 0x10, transac);
	this->actionType = 0;
}
ComplexInventoryTransaction::ComplexInventoryTransaction() {
	memset(this, 0, sizeof(ComplexInventoryTransaction));
	static uintptr_t** ComplexInventoryTransactionVtable = 0x0;
	if (ComplexInventoryTransactionVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("4C 8D 3D ? ? ? ? 4C 89 7D ? E8 ? ? ? ? 48 89 45 ? 89 75");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		ComplexInventoryTransactionVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (ComplexInventoryTransactionVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	vTable = ComplexInventoryTransactionVtable;
}
ItemUseInventoryTransaction::ItemUseInventoryTransaction() {
	memset(this, 0x0, sizeof(ItemUseInventoryTransaction));
	using ItemUseInventoryTransactionContructor = void(__fastcall*)(ItemUseInventoryTransaction*);
	static ItemUseInventoryTransactionContructor constructor = reinterpret_cast<ItemUseInventoryTransactionContructor>(FindSignature("48 8D 05 ? ? ? ? 48 89 07 48 8D 8F ? ? ? ? 48 8D 96 ? ? ? ? E8 ? ? ? ? 48 8B 86"));
	if (constructor != 0)
		constructor(this);
}
ItemUseInventoryTransaction::ItemUseInventoryTransaction(int slot, const ItemStack* item, const Vec3 pos, int blockSide, int runtimeBlockId) {
	memset(this, 0x0, sizeof(ItemUseInventoryTransaction));
	using ItemUseInventoryTransactionContructor = void(__fastcall*)(ItemUseInventoryTransaction*);
	static ItemUseInventoryTransactionContructor constructor = reinterpret_cast<ItemUseInventoryTransactionContructor>(FindSignature("48 8D 05 ? ? ? ? 48 89 07 48 8D 8F ? ? ? ? 48 8D 96 ? ? ? ? E8 ? ? ? ? 48 8B 86"));
	if (constructor != 0)
		constructor(this);
	this->slot = slot;
	this->item = *item;
	this->pos = pos;
	this->runtimeBlockId = runtimeBlockId;
	this->blockSide = blockSide;
}
ItemReleaseInventoryTransaction::ItemReleaseInventoryTransaction() {
	memset(this, 0x0, sizeof(ItemReleaseInventoryTransaction));
	using ItemReleaseInventoryTransactionContructor = void(__fastcall*)(ItemReleaseInventoryTransaction*);
	static ItemReleaseInventoryTransactionContructor constructor = reinterpret_cast<ItemReleaseInventoryTransactionContructor>(FindSignature("48 8D 05 ? ? ? ? 48 8B F1 48 89 01 8B FA 48 83 C1 ? E8 ? ? ? ? 48 8D 4E ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 06 40 F6 C7 ? 74 0D BA ? ? ? ? 48 8B CE E8 ? ? ? ? 48 8B 5C ? ? 48 8B C6 48 8B 74 ? ? 48 83 C4 ? 5F C3 48 89 5C ? ? 57"));
	if (constructor != 0)
		constructor(this);
}
ItemReleaseInventoryTransaction::ItemReleaseInventoryTransaction(int slot, const ItemStack* item, const Vec3 pos) {
	memset(this, 0x0, sizeof(ItemReleaseInventoryTransaction));
	using ItemReleaseInventoryTransactionContructor = void(__fastcall*)(ItemReleaseInventoryTransaction*);
	static ItemReleaseInventoryTransactionContructor constructor = reinterpret_cast<ItemReleaseInventoryTransactionContructor>(FindSignature("48 8D 05 ? ? ? ? 48 8B F1 48 89 01 8B FA 48 83 C1 ? E8 ? ? ? ? 48 8D 4E ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 06 40 F6 C7 ? 74 0D BA ? ? ? ? 48 8B CE E8 ? ? ? ? 48 8B 5C ? ? 48 8B C6 48 8B 74 ? ? 48 83 C4 ? 5F C3 48 89 5C ? ? 57"));
	if (constructor != 0)
		constructor(this);
	this->slot = slot;
	this->item = *item;
	this->pos = pos;
}
