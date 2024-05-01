#include "Nbt.h"
#include "../../../SDK/Tag.h"
#include "../../../Utils/Utils.h"

Nbt::Nbt() : IModule(0, Category::PLAYER, "Print NBT tags when you right click on mobs (Only works on local worlds!).") {
}

Nbt::~Nbt() {
}

const char* Nbt::getModuleName() {
	return "Nbt";
}

void Nbt::onTick(GameMode* gm) {
	if (!GameData::canUseMoveKeys()) {
		return;
	}
	Level* level = Game.getLocalPlayer()->level;
	
	if (GameData::isRightClickDown()) {  // && Utils::getClipboardText() != lastCopy) {
		if (level->getEntity() != nullptr) {

			if (Game.getRakNetConnector()->isonaServer())
				return;
			std::unique_ptr<CompoundTag> tag = std::make_unique<CompoundTag>();
			level->getEntity()->save(tag.get());
			std::stringstream build;
			tag->write(build);
			auto str = build.str();
			if (lastCopy == str)
				return;
			lastCopy = str;
			Utils::setClipboardText(lastCopy);
			Game.getGuiData()->displayClientMessageF("%s%s", GREEN, "CompoundTag copied:");
			Game.getClientInstance()->getGuiData()->displayClientMessage(&str);
		}
	}
}
