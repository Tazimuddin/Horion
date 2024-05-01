#include "AutoArmor.h"
#include "../../../Utils/Utils.h"
#include "../../../Utils/Logger.h"

class ArmorStruct {
public:
	ArmorStruct(ItemStack* item, ArmorItem* yot, int slot) {
		armor = yot;
		m_slot = slot;
		m_item = item;
	}
	bool isEqual(ArmorStruct& src) {
		if (m_item->getArmorValueWithEnchants() == src.m_item->getArmorValueWithEnchants())
			return true;
		else
			return false;
	}

	bool operator()(ArmorStruct lhs, ArmorStruct rhs) {
		return (lhs.m_item->getArmorValueWithEnchants() > rhs.m_item->getArmorValueWithEnchants());
	}
	ArmorItem* armor = nullptr;
	ItemStack* m_item = nullptr;
	int m_slot = 0;
};

AutoArmor::AutoArmor() : IModule(0, Category::PLAYER, "Automatically equips the best armor.") {
}

AutoArmor::~AutoArmor() {
}

const char* AutoArmor::getModuleName() {
	return "AutoArmor";
}

void AutoArmor::onTick(GameMode* gm) {
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	InventoryTransactionManager* manager = Game.getLocalPlayer()->getTransactionManager();

	InventoryAction* first = nullptr;
	InventoryAction* second = nullptr;
	static ItemStack* emptyItemStack = nullptr;

	if (emptyItemStack == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 1D ? ? ? ? 80 BA ? ? ? ? ? 75 ? 48 8B 8A ? ? ? ? 48 8B 01");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		emptyItemStack = reinterpret_cast<ItemStack*>(sigOffset + offset + /*length of instruction*/ 7);
	}

	std::vector<ArmorStruct> armorList;

	struct CompareArmorStruct {
		bool operator()(ArmorStruct lhs, ArmorStruct rhs) {
			return (lhs.m_item->getArmorValueWithEnchants() > rhs.m_item->getArmorValueWithEnchants());
		}
	};

	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 36; n++) {
			ItemStack* stack = inv->getItemStack(n);
			if (stack->item != NULL && (*stack->item)->isArmor() && reinterpret_cast<ArmorItem*>(*stack->item)->ArmorSlot == i) {
				armorList.push_back(ArmorStruct(stack, reinterpret_cast<ArmorItem*>(*stack->item), n));
			}
		}

		if (gm->player->getArmor(i)->item != nullptr)
			armorList.push_back(ArmorStruct(gm->player->getArmor(i), reinterpret_cast<ArmorItem*>(*gm->player->getArmor(i)->item), i));

		if (armorList.size() > 0) {
			std::sort(armorList.begin(), armorList.end(), CompareArmorStruct());
			ItemStack* armorItem = gm->player->getArmor(i);

			if (armorItem->item != nullptr && (ArmorStruct(armorItem, reinterpret_cast<ArmorItem*>(*armorItem->item), 0).isEqual(armorList[0])) == false) {
				int slot = inv->getFirstEmptySlot();

				first = new InventoryAction(i, armorItem, nullptr, InventorySource(ContainerInventory, Armor, NoFlag));
				second = new InventoryAction(slot, nullptr, armorItem);

				*Game.getLocalPlayer()->getArmor(i) = *emptyItemStack;
				*inv->getItemStack(slot) = *armorItem;

				manager->addInventoryAction(*first);
				manager->addInventoryAction(*second);

				delete first;
				delete second;

				first = new InventoryAction(armorList[0].m_slot, armorList[0].m_item, nullptr);
				second = new InventoryAction(i, nullptr, armorList[0].m_item, InventorySource(ContainerInventory, Armor, NoFlag));

				*Game.getLocalPlayer()->getArmor(i) = *inv->getItemStack(armorList[0].m_slot);
				*inv->getItemStack(armorList[0].m_slot) = *emptyItemStack;

				manager->addInventoryAction(*first);
				manager->addInventoryAction(*second);

				delete first;
				delete second;
			}
			if (armorItem->item == nullptr) {
				*Game.getLocalPlayer()->getArmor(i) = *inv->getItemStack(armorList[0].m_slot);

				first = new InventoryAction(armorList[0].m_slot, armorList[0].m_item, nullptr);
				second = new InventoryAction(i, nullptr, armorList[0].m_item, InventorySource(ContainerInventory, Armor, NoFlag));

				*inv->getItemStack(armorList[0].m_slot) = *emptyItemStack;

				manager->addInventoryAction(*first);
				manager->addInventoryAction(*second);

				delete first;
				delete second;
			}
		}
		armorList.clear();
	}
	armorList.clear();
}
