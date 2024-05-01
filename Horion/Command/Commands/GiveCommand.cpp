#include "GiveCommand.h"

#include "../../../SDK/Tag.h"
#include "../../../Utils/Utils.h"

GiveCommand::GiveCommand() : IMCCommand("give", "spawn items", "<itemName> <count> [itemData] [NBT]") {
}

GiveCommand::~GiveCommand() {
}
bool isValidNBT(std::string &tag) {
	return tag.size() > 1 && tag.front() == MojangsonToken::COMPOUND_START.getSymbol() && tag.back() == MojangsonToken::COMPOUND_END.getSymbol();
}

bool GiveCommand::execute(std::vector<std::string> *args) {
	assertTrue(args->size() > 2);

	int itemId = 0;
	uint32_t fullCount = static_cast<uint32_t>(assertInt(args->at(2)));
	unsigned int stackCount = fullCount / 64;
	unsigned int count = fullCount % 64;
	unsigned int itemData = 0;

	if (args->size() > 3) {
		itemData = assertInt(args->at(3));
	}

	try {
		itemId = std::stoi(args->at(1));
	} catch (const std::invalid_argument &) {
	}

	for (unsigned int i = 0; i < stackCount; i++) {
		std::string tag;
		bool success = false;

		if (args->size() > 4) {
			tag = Utils::getClipboardText();
		}

		if (itemId == 0) {
			TextHolder tempText(args->at(1));
			success = giveItem(64, tempText, itemData, tag);
		} else {
			success = giveItem(64, itemId, itemData, tag);
		}

		if (!success) {
			return true;
		}
	}

	if (count >= 1) {
		std::string tag;
		bool success = false;

		if (args->size() > 4) {
			tag = Utils::getClipboardText();
		}

		if (itemId == 0) {
			TextHolder tempText(args->at(1));
			success = giveItem(count, tempText, itemData, tag);
		} else {
			success = giveItem(count, itemId, itemData, tag);
		}

		if (!success) {
			return true;
		}
	}

	Inventory *inv = Game.getLocalPlayer()->getSupplies()->inventory;
	ItemStack *item = Game.getLocalPlayer()->getSelectedItem();

	if (args->size() > 4) {
		std::string tag = Utils::getClipboardText();

		if (isValidNBT(tag)) {
			item->setUserData(std::move(Mojangson::parseTag(tag)));
		} else {
			clientMessageF("%sInvalid NBT tag!", RED);
			return true;
		}

		if (args->size() > 4) {
			Game.getLocalPlayer()->getTransactionManager()->addInventoryAction(InventoryAction(0, item, nullptr, InventorySource(NonImplementedFeatureTODO, inventory, NoFlag)));
		}

		clientMessageF("%s%s", GREEN, "Successfully loaded mojangson !");
	}

	if (args->size() > 4) {
		InventoryAction *firstAction = nullptr;
		auto transactionMan = Game.getLocalPlayer()->getTransactionManager();
		firstAction = new InventoryAction(0, item, nullptr);
		transactionMan->addInventoryAction(*firstAction);
		inv->addItemToFirstEmptySlot(item);
		delete firstAction;
	}

	clientMessageF("%sSuccessfully gave items!", GREEN);
	return true;
}

bool GiveCommand::giveItem(uint8_t count, int itemId, uint8_t itemData, std::string &tag) {
	Inventory *inv = Game.getLocalPlayer()->getSupplies()->inventory;
	ItemStack *itemStack = nullptr;
	auto transactionManager = Game.getLocalPlayer()->getTransactionManager();

	void *ItemPtr;
	Item ***cStack = ItemRegistry::getItemFromId(&ItemPtr, itemId);

	if (cStack == nullptr || *cStack == nullptr || **cStack == nullptr) {
		clientMessageF("%sInvalid item ID!", RED);
		return false;
	}

	itemStack = new ItemStack(***cStack, count, itemData);
	int slot = inv->getFirstEmptySlot();

	if (tag.size() > 1 && tag.front() == MojangsonToken::COMPOUND_START.getSymbol() && tag.back() == MojangsonToken::COMPOUND_END.getSymbol()) {
		itemStack->fromTag(*Mojangson::parseTag(tag));
	}

	InventoryAction *firstAction = new InventoryAction(slot, itemStack, nullptr, InventorySource(NonImplementedFeatureTODO, inventory, NoFlag));
	transactionManager->addInventoryAction(*firstAction);
	inv->addItemToFirstEmptySlot(itemStack);

	delete firstAction;
	return true;
}

bool GiveCommand::giveItem(uint8_t count, TextHolder &text, uint8_t itemData, std::string &tag) {
	Inventory *inv = Game.getLocalPlayer()->getSupplies()->inventory;
	ItemStack *itemStack = nullptr;
	auto transactionManager = Game.getLocalPlayer()->getTransactionManager();

	void *ItemPtr;
	void *buffer;
	Item ***cStack = ItemRegistry::lookUpByName(&ItemPtr, &buffer, text);

	if (*cStack == nullptr) {
		clientMessageF("%sInvalid item name!", RED);
		return false;
	}

	itemStack = new ItemStack(***cStack, count, itemData);
	int slot = inv->getFirstEmptySlot();

	if (tag.size() > 1 && tag.front() == MojangsonToken::COMPOUND_START.getSymbol() && tag.back() == MojangsonToken::COMPOUND_END.getSymbol()) {
		itemStack->fromTag(*Mojangson::parseTag(tag));
	}

	InventoryAction *firstAction = new InventoryAction(slot, itemStack, nullptr, InventorySource(NonImplementedFeatureTODO, inventory, NoFlag));
	transactionManager->addInventoryAction(*firstAction);
	inv->addItemToFirstEmptySlot(itemStack);

	delete firstAction;
	return true;
}