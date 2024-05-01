#include "EnchantCommand.h"

#include "../../../Utils/Utils.h"

EnchantCommand::EnchantCommand() : IMCCommand("enchant", "Enchants items", "<enchantment> [level] <mode: auto / manual : 1/0>") {
	enchantMap["protection"] = 0;
	enchantMap["fire_protection"] = 1;
	enchantMap["feather_falling"] = 2;
	enchantMap["blast_protection"] = 3;
	enchantMap["projectile_protection"] = 4;
	enchantMap["thorns"] = 5;
	enchantMap["respiration"] = 6;
	enchantMap["depth_strider"] = 7;
	enchantMap["aqua_affinity"] = 8;
	enchantMap["frost_walker"] = 25;
	enchantMap["sharpness"] = 9;
	enchantMap["smite"] = 10;
	enchantMap["bane_of_arthropods"] = 11;
	enchantMap["knockback"] = 12;
	enchantMap["fire_aspect"] = 13;
	enchantMap["looting"] = 14;
	enchantMap["channeling"] = 32;
	enchantMap["impaling"] = 29;
	enchantMap["loyalty"] = 31;
	enchantMap["riptide"] = 30;
	enchantMap["silktouch"] = 16;
	enchantMap["fortune"] = 18;
	enchantMap["unbreaking"] = 17;
	enchantMap["efficiency"] = 15;
	enchantMap["mending"] = 26;
	enchantMap["power"] = 19;
	enchantMap["punch"] = 20;
	enchantMap["flame"] = 21;
	enchantMap["infinity"] = 22;
	enchantMap["multishot"] = 33;
	enchantMap["quick_charge"] = 35;
	enchantMap["piercing"] = 34;
	enchantMap["luck_of_sea"] = 23;
	enchantMap["lure"] = 24;
	enchantMap["soul_speed"] = 36;
}

EnchantCommand::~EnchantCommand() {
}

bool EnchantCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	int enchantId = 0;
	int enchantLevel = 32767;
	bool isAuto = true;

	if (args->at(1) != "all") {
		try {
			// convert string to lower case
			std::string data = args->at(1);
			std::transform(data.begin(), data.end(), data.begin(), ::tolower);

			auto it = enchantMap.find(data);
			if (it != enchantMap.end()) {
				enchantId = it->second;
			} else {
				enchantId = assertInt(args->at(1));
			}
		} catch (int) {
			clientMessageF("Exception while trying to get enchant string");
			enchantId = assertInt(args->at(1));
		}
	}

	if (args->size() > 2) {
		enchantLevel = assertInt(args->at(2));
	}
	if (args->size() > 3) {
		isAuto = static_cast<bool>(assertInt(args->at(3)));
	}

	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	InventoryTransactionManager* manager = Game.getLocalPlayer()->getTransactionManager();
	int selectedSlot = supplies->selectedHotbarSlot;
	ItemStack* item = inv->getItemStack(selectedSlot);
	InventoryAction* firstAction = nullptr;
	InventoryAction* secondAction = nullptr;

	if (item == nullptr || item->item == nullptr) {
		clientMessageF("Please hold an item!");
		return false;
	}

	if (isAuto) {
		firstAction = new InventoryAction(supplies->selectedHotbarSlot, item, nullptr, InventorySource(ContainerInventory, inventory, NoFlag));
		secondAction = new InventoryAction(0, nullptr, item, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag));
		manager->addInventoryAction(*firstAction);
		manager->addInventoryAction(*secondAction);
		delete firstAction;
		delete secondAction;
	}

	using getEnchantsFromUserData_t = void(__fastcall*)(ItemStack*, void*);
	using addEnchant_t = bool(__fastcall*)(void*, __int64);
	using saveEnchantsToUserData_t = void(__fastcall*)(ItemStack*, void*);

	static getEnchantsFromUserData_t getEnchantsFromUserData = reinterpret_cast<getEnchantsFromUserData_t>(FindSignature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B FA 48 8B F1 33 DB"));
	static addEnchant_t addEnchant = reinterpret_cast<addEnchant_t>(FindSignature("48 89 5C 24 ?? 48 89 54 24 ?? 57 48 83 EC ?? 45 0F"));
	static saveEnchantsToUserData_t saveEnchantsToUserData = 0x0;

	if (!saveEnchantsToUserData) {
		saveEnchantsToUserData = reinterpret_cast<saveEnchantsToUserData_t>(FindSignature("48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 48 8B FA 4C 8B C1"));
	}

	if (strcmp(args->at(1).c_str(), "all") == 0) {
		for (int i = 0; i < 38; i++) {
			void* enchantData = malloc(0x60);
			if (enchantData != nullptr) {
				memset(enchantData, 0x0, 0x60);
			}

			getEnchantsFromUserData(item, enchantData);

			__int64 enchantPair = ((__int64)enchantLevel << 32) | i;

			if (addEnchant(enchantData, enchantPair)) {  // Upper 4 bytes = level, lower 4 bytes = enchant type
				saveEnchantsToUserData(item, enchantData);
				__int64 proxy = reinterpret_cast<__int64>(Game.getLocalPlayer()->getSupplies());
				if (!*(uint8_t*)(proxy + 168)) {
					(*(void(__fastcall**)(unsigned long long, unsigned long long, ItemStack*))(**(unsigned long long**)(proxy + 192) + 72i64))(
						*(unsigned long long*)(proxy + 192),
						*(unsigned int*)(proxy + 16),
						item);  // Player::selectItem
				}
				// Game.getLocalPlayer()->sendInventory();
			}
			free(enchantData);
		}
		clientMessageF("%sEnchant successful!", GREEN);
	} else {
		void* enchantData = malloc(0x60);
		if (enchantData != nullptr) {
			memset(enchantData, 0x0, 0x60);
		}

		getEnchantsFromUserData(item, enchantData);

		__int64 enchantPair = ((__int64)enchantLevel << 32) | enchantId;

		if (addEnchant(enchantData, enchantPair)) {  // Upper 4 bytes = level, lower 4 bytes = enchant type
			saveEnchantsToUserData(item, enchantData);
			__int64 proxy = reinterpret_cast<__int64>(Game.getLocalPlayer()->getSupplies());
			if (!*(uint8_t*)(proxy + 168)) {
				(*(void(__fastcall**)(unsigned long long, unsigned long long, ItemStack*))(**(unsigned long long**)(proxy + 176) + 72i64))(
					*(unsigned long long*)(proxy + 192),
					*(unsigned int*)(proxy + 16),
					item);  // Player::selectItem
			}
			// Game.getLocalPlayer()->sendInventory();
			clientMessageF("%sEnchant successful!", GREEN);
		} else {
			clientMessageF("%sEnchant failed, try using a lower enchant level", RED);
		}

		free(enchantData);
	}

	if (isAuto) {
		firstAction = new InventoryAction(0, item, nullptr, InventorySource(NonImplementedFeatureTODO, Invalid, NoFlag));
		secondAction = new InventoryAction(supplies->selectedHotbarSlot, nullptr, item, InventorySource(ContainerInventory, inventory, NoFlag));
		manager->addInventoryAction(*firstAction);
		manager->addInventoryAction(*secondAction);
		delete firstAction;
		delete secondAction;
	}
	return true;
}