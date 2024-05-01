#include "NoWeb.h"
#include "OffhandAllow.h"

OffhandAllow::OffhandAllow() : IModule(0, Category::MISC, "Let's you place any item in your offhand") {}

OffhandAllow::~OffhandAllow() {}

const char* OffhandAllow::getModuleName() {
	return "OffhandAllow";
}

void OffhandAllow::onEnable() {
	LocalPlayer* player = Game.getLocalPlayer();
	if (player != nullptr) {
		Inventory* inv = player->getSupplies()->inventory;
		for (int i = 0; i <= 36; i++) {
			ItemStack* itemStack = inv->getItemStack(i);
			if (itemStack == nullptr || itemStack->item == nullptr)
				return;
			else {
				Item* item = itemStack->getItem();
				item->setAllowOffhand();
			}
		}
		return;
	}
}