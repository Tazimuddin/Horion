#include "Reducer.h"

Reducer::Reducer() : IModule(0, Category::COMBAT, "Tries do reduce your knockback relatively legit") {
	this->mode.addEntry(EnumEntry("Jump", 0))
			   .addEntry(EnumEntry("Sneak", 1))
			   .addEntry(EnumEntry("JumpReset", 2));
	this->registerEnumSetting("Mode", &this->mode, 0);
}

Reducer::~Reducer() {
}

const char* Reducer::getModuleName() {
	if (this->isEnabled()) {
		static char modName[64];
		snprintf(modName, 64, "Reducer [%s]", this->mode.GetSelectedEntry().GetName().c_str());
		return modName;
	}

	return "Reducer";
}

const char* Reducer::getRawModuleName() {
	return "Reducer";
}

void Reducer::onEnable() {
	if (Game.getLocalPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}

	this->hitCount = 0;
	this->ticks = 0;
}

void Reducer::onTick(GameMode* gm) {
	if (Game.getLocalPlayer() == nullptr) return;

	LocalPlayer* player = Game.getLocalPlayer();

	switch (this->mode.selected) {
	case 0:
		if (player->damageTime > 0 && player->isOnGround())
			player->jumpFromGround();
		break;
	case 1:
		if (player->damageTime > 0 && !player->isSneaking()) {
			player->setSneaking(true);
			player->setSneaking(false);
		}
		break;
	case 2:
		ticks++;

		if (player->damageTime == 1)
			this->hitCount++;

		if (player->damageTime > 0)
			this->ticks = 0;

		if (this->ticks >= 20)
			this->hitCount = 0;

		if (player->damageTime > 0 && this->hitCount == 2 && player->isOnGround()) {
			player->jumpFromGround();
			this->hitCount = 0;
		}
		break;
	}
}
