#pragma once
#include "../Utils/HMath.h"
#include "Inventory.h"
#include "Item.h"

enum InventorySourceType : int32_t {
	InvalidInventory = -1,
	ContainerInventory = 0,
	GlobalInventory = 1,
	WorldInteraction = 2,
	CreativeInventory = 3,
	//UntrackedInteractionUI = 100,
	NonImplementedFeatureTODO = 99999,
	EnchantStuff = 32766,
};

enum ContainerID : uint8_t {
	Invalid = 0xFF,
	inventory = 0, //needs to be lower case bec stupidness
	First = 1,
	Last = 100,
	Offhand = 119,
	Armor = 120,
	SelectionSlots = 122,
	PlayerUIOnly = 124
};

enum InventorySourceFlags : int32_t {
	NoFlag = 0,
	WorldInteraction_Random = 1,
};

class InventorySource {
public:
	InventorySource::InventorySourceType type;
	InventorySource::ContainerID containerId;
	InventorySource::InventorySourceFlags flags;

	InventorySource() = default;
	InventorySource(InventorySourceType mType, ContainerID mContainerId, InventorySourceFlags mFlags) {
		this->type = mType;
		this->containerId = mContainerId;
		this->flags = mFlags;
	}
};

class InventoryAction {
public:
	void fixInventoryStuff(ItemDescriptor* a1, ItemStack* a2);
	InventoryAction() = default;
	InventoryAction(int slot, ItemStack* sourceItem, ItemStack* targetItem, InventorySource invSource = InventorySource(NonImplementedFeatureTODO, inventory, NoFlag)) {
		memset(this, 0x0, sizeof(InventoryAction));
		this->slot = slot;
		if (sourceItem != nullptr) {
			this->sourceItem = *sourceItem;
		}
		if (targetItem != nullptr) {
			this->targetItem = *targetItem;
		}
		this->sourceItemDescriptor.fromStack(&this->sourceItem);
		this->targetItemDescriptor.fromStack(&this->targetItem);
		fixInventoryStuff(reinterpret_cast<ItemDescriptor*>(reinterpret_cast<__int64>(this) + 0x10), reinterpret_cast<ItemStack*>(reinterpret_cast<__int64>(this) + 0x140));
		fixInventoryStuff(reinterpret_cast<ItemDescriptor*>(reinterpret_cast<__int64>(this) + 0xA8), reinterpret_cast<ItemStack*>(reinterpret_cast<__int64>(this) + 0x1E0));
		this->inventorySource = invSource;
	}

public:
	InventorySource inventorySource;
	int slot;                             //0xC
	ItemDescriptor sourceItemDescriptor;  //0x10
	ItemDescriptor targetItemDescriptor;  //0x90
	ItemStack sourceItem;  //0x110
	ItemStack targetItem;  //0x1A0
};

class InventoryTransaction {};

class InventoryTransactionManager {
public:
	uintptr_t* player;               //0x0
	InventoryTransaction transac;  //0x8
private:
	int unknown;  //0x60
				  // Total size: 0x68
public:
	void addInventoryAction(InventoryAction const& action, bool forceBalanced = false);
};