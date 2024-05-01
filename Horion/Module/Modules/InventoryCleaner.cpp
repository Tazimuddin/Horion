#include "InventoryCleaner.h"

#include "../ModuleManager.h"

InventoryCleaner::InventoryCleaner() : IModule(0, Category::PLAYER, "Automatically throws not needed stuff out of your inventory.") {
	registerBoolSetting("Tools", &keepTools, keepTools);
	registerBoolSetting("Armor", &keepArmor, keepArmor);
	registerBoolSetting("Food", &keepFood, keepFood);
	registerBoolSetting("Blocks", &keepBlocks, keepBlocks);
	registerBoolSetting("OpenInv", &openInv, openInv);
	registerBoolSetting("AutoSort", &autoSort, autoSort);
}

InventoryCleaner::~InventoryCleaner() {
}

const char* InventoryCleaner::getModuleName() {
	return "InvCleaner";
}

void InventoryCleaner::onTick(GameMode* gm) {
	if (Game.getLocalPlayer()->canOpenContainerScreen() && openInv) 
		return;

	// Drop useless items
	std::vector<int> dropSlots = findUselessItems();
	if (!dropSlots.empty()) {
		for (int i : dropSlots) {
			Game.getLocalPlayer()->getSupplies()->inventory->dropSlot(i);
		}
	}

	if (autoSort) {
		// Put sword in first slot
		{
			PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
			Inventory* inv = supplies->inventory;
			float damage = 0;
			int item = 0;
			for (int n = 0; n < 36; n++) {
				ItemStack* stack = inv->getItemStack(n);
				if (stack->item != NULL) {
					float currentDamage = stack->getAttackingDamageWithEnchants();
					if (currentDamage > damage) {
						damage = currentDamage;
						item = n;
					}
				}
			}
			if (item != 0) inv->moveItem(item, 0);
		}
	}
}

std::vector<int> InventoryCleaner::findStackableItems() {
	std::vector<int> stackableSlot;

	for (int i = 0; i < 36; i++) {
		ItemStack* itemStack = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (itemStack->item != nullptr) {
			if ((*itemStack->item)->getMaxStackSize(0) > itemStack->count) {
				for (int i2 = 0; i2 < 36; i2++) {
					if (i2 == i) continue;
					ItemStack* itemStack2 = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i2);
					if ((*itemStack2->item)->getMaxStackSize(0) > itemStack->count) {
						if (*itemStack->item == *itemStack2->item) {
							if ((std::find(stackableSlot.begin(), stackableSlot.end(), i2) == stackableSlot.end())) stackableSlot.push_back(i2);
							if ((std::find(stackableSlot.begin(), stackableSlot.end(), i) == stackableSlot.end())) stackableSlot.push_back(i);
						}
					}
				}
			}
		}
	}

	return stackableSlot;
}

std::vector<int> InventoryCleaner::findUselessItems() {
	// Filter by options

	std::vector<int> uselessItems;
	std::vector<ItemStack*> items;

	{
		for (int i = 0; i < 36; i++) {
			ItemStack* itemStack = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (itemStack->item != nullptr) {
				if (!stackIsUseful(itemStack)) {
					if (std::find(items.begin(), items.end(), itemStack) == items.end())
						uselessItems.push_back(i);
					else
						items.push_back(itemStack);
				} else if (std::find(items.begin(), items.end(), itemStack) == items.end()) {
					if ((*itemStack->item)->itemId == 261 && !isLastItem(*itemStack->item))
						uselessItems.push_back(i);
					else
						items.push_back(itemStack);	
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			if (Game.getLocalPlayer()->getArmor(i)->item != nullptr)
				items.push_back(Game.getLocalPlayer()->getArmor(i));
		}
	}
	// Filter weapons
	if (items.size() > 0) {
		// Filter by attack damage
		std::sort(items.begin(), items.end(), [](const ItemStack* lhs, const ItemStack* rhs) {
			ItemStack* current = const_cast<ItemStack*>(lhs);
			ItemStack* other = const_cast<ItemStack*>(rhs);
			return current->getAttackingDamageWithEnchants() > other->getAttackingDamageWithEnchants();
		});

		bool hadTheBestItem = false;
		ItemStack* bestItem = items.at(0);

		for (int i = 0; i < 36; i++) {
			if (std::find(uselessItems.begin(), uselessItems.end(), i) != uselessItems.end())
				continue;
			ItemStack* itemStack = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (itemStack->item != nullptr && itemStack->getAttackingDamageWithEnchants() > 1) {
				if (itemStack->getAttackingDamageWithEnchants() < bestItem->getAttackingDamageWithEnchants()) {
					uselessItems.push_back(i);
				} else {
					// Damage same as bestItem
					if (hadTheBestItem)
						uselessItems.push_back(i);
					else
						hadTheBestItem = true;
				}
			}
		}
	}
	// Filter armor
	{
		std::vector<ItemStack*> helmets;
		std::vector<ItemStack*> chestplates;
		std::vector<ItemStack*> leggings;
		std::vector<ItemStack*> boots;

		// Filter by armor value
		std::sort(items.begin(), items.end(), [](const ItemStack* lhs, const ItemStack* rhs) {
			ItemStack* current = const_cast<ItemStack*>(lhs);
			ItemStack* other = const_cast<ItemStack*>(rhs);
			return current->getArmorValueWithEnchants() > other->getArmorValueWithEnchants();
		});

		// Put armor items in their respective vectors
		for (ItemStack* itemsteck : items) {
			Item* item = itemsteck->getItem();
			if (item->isArmor()) {
				ArmorItem* armorItem = reinterpret_cast<ArmorItem*>(item);
				if (armorItem->isHelmet())
					helmets.push_back(itemsteck);
				else if (armorItem->isChestplate())
					chestplates.push_back(itemsteck);
				else if (armorItem->isLeggings())
					leggings.push_back(itemsteck);
				else if (armorItem->isBoots())
					boots.push_back(itemsteck);
			}
		}
		bool hadBest[4] = {0, 0, 0, 0};
		for (int i = 0; i < 4; i++) {
			ItemStack* itemsteck = Game.getLocalPlayer()->getArmor(i);
			Item** item = itemsteck->item;
			if (item != nullptr) {
				
				ArmorItem* armor = reinterpret_cast<ArmorItem*>(*item);
				
				float testArmorValue = 0;
				switch (armor->ArmorSlot) {
				case 0:
					if (helmets.size() > 0)
						testArmorValue = helmets.at(0)->getArmorValueWithEnchants();
					break;
				case 1:
					if (chestplates.size() > 0)
						testArmorValue = chestplates.at(0)->getArmorValueWithEnchants();
					break;
				case 2:
					if (leggings.size() > 0)
						testArmorValue = leggings.at(0)->getArmorValueWithEnchants();
					break;
				case 3:
					if (boots.size() > 0)
						testArmorValue = boots.at(0)->getArmorValueWithEnchants();
					break;
				}
				if (itemsteck->getArmorValueWithEnchants() >= testArmorValue)
					hadBest[armor->ArmorSlot] = true;
			}
		}

		for (int i = 0; i < 36; i++) {
			if (std::find(uselessItems.begin(), uselessItems.end(), i) != uselessItems.end())
				continue;  // item already useless
			ItemStack* itemStack = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
			if (itemStack->item != nullptr && (*itemStack->item)->isArmor()) {
				ArmorItem* armor = reinterpret_cast<ArmorItem*>(*itemStack->item);
				if (armor->isHelmet()) {
					if (hadBest[0] || itemStack->getArmorValueWithEnchants() < helmets.at(0)->getArmorValueWithEnchants()) {
						uselessItems.push_back(i);
					} else
						hadBest[0] = true;
				} else if (armor->isChestplate()) {
					if (hadBest[1] || itemStack->getArmorValueWithEnchants() < chestplates.at(0)->getArmorValueWithEnchants())
						uselessItems.push_back(i);
					else
						hadBest[1] = true;
				} else if (armor->isLeggings()) {
					if (hadBest[2] || itemStack->getArmorValueWithEnchants() < leggings.at(0)->getArmorValueWithEnchants())
						uselessItems.push_back(i);
					else
						hadBest[2] = true;
				} else if (armor->isBoots()) {
					if (hadBest[3] || itemStack->getArmorValueWithEnchants() < boots.at(0)->getArmorValueWithEnchants())
						uselessItems.push_back(i);
					else
						hadBest[3] = true;
				}
			}
		}
	}

	return uselessItems;
}

bool InventoryCleaner::stackIsUseful(ItemStack* itemStack) {
	if (itemStack->item == nullptr) return true;
	if (keepArmor && (*itemStack->item)->isArmor()) return true;      // Armor
	if (keepTools && (*itemStack->item)->isTool()) return true;       // Tools
	if (keepFood && (*itemStack->item)->isFood()) return true;        // Food
	if (keepBlocks && (*itemStack->item)->isBlock()) return true;     // Block
	if (keepTools && (*itemStack->item)->itemId == 368) return true;  // Ender Pearl
	return false;
}

bool InventoryCleaner::isLastItem(Item* item) {
	std::vector<Item*> items;
	for (int i = 0; i < 36; i++) {
		ItemStack* stack = Game.getLocalPlayer()->getSupplies()->inventory->getItemStack(i);
		if (stack->item != nullptr) items.push_back((*stack->item));
	}
	int count = 0;
	for (Item* a : items) {
		if (a == item) count++;
	}
	if (count > 1) return false;
	return true;
}
