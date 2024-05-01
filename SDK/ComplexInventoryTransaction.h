#pragma once
#include "../Utils/HMath.h"
#include "Inventory.h"
#include "InventoryTransaction.h"

class ComplexInventoryTransaction {
public:
	ComplexInventoryTransaction();
	ComplexInventoryTransaction(InventoryTransaction& transac);
	uintptr_t** vTable;              //0x0000
	int actionType;                  //0x8
	int unknown;                     //0xC
	InventoryTransaction transac;  //0x10
};

class ItemUseInventoryTransaction : public ComplexInventoryTransaction {
public:
	ItemUseInventoryTransaction();
	ItemUseInventoryTransaction(int slot, ItemStack const* item, Vec3 const pos, int blockSide = 255, int runtimeBlockId = 0);

private:
	char pad_0x68[0x4];  //0x68
public:
	Vec3i blockPos;    //0x6C
	int runtimeBlockId;  //0x78
	int blockSide;       //0x7C
	int slot;            //0x80
private:
	char pad_0x84[0x4];  //0x84
public:
	ItemStack item;  //0x88
	Vec3 pos;        //0x110
	Vec3 clickPos;   //0x11C
};

class ItemReleaseInventoryTransaction : public ComplexInventoryTransaction {
public:
	ItemReleaseInventoryTransaction();
	ItemReleaseInventoryTransaction(int slot, ItemStack const* item, Vec3 const pos);

private:
	char pad_0x68[0x4];  //0x68
public:
	int slot;          //0x6C
	ItemStack item;  //0x70
	Vec3 pos;        //0xF8
	int unknown;       //0x104
};
