#include "NoEntityRender.h"

NoEntityRender::NoEntityRender() : IModule(0x0, Category::VISUAL, "Un-renders certain entities") {
	registerBoolSetting("FallingBlocks", &this->isFallingBlock, this->isFallingBlock);
	registerBoolSetting("PrimedTnt", &this->isTNT, this->isTNT);
	registerBoolSetting("Paintings", &this->isPainting, this->isPainting);
	registerBoolSetting("ArmourStands", &this->isArmourStand, this->isArmourStand);
	registerBoolSetting("Boats", &this->isBoat, this->isBoat);
	registerBoolSetting("Minecarts", &this->isMinecart, this->isMinecart);
	registerBoolSetting("Items", &this->isItems, this->isItems);
	registerBoolSetting("Skin Crash", &this->isPlayers, this->isPlayers);
	registerBoolSetting("XP", &this->isXp, this->isXp);
}

NoEntityRender::~NoEntityRender() {
}

const char* NoEntityRender::getModuleName() {
	return ("NoRender");
}

static std::vector<Entity*> targetList;

void boats(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void fallingblocks(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 66)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void painting(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 83)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void Items(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 64)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void Players(Entity* currentEntity, bool isRegularEntity) {
	LocalPlayer* player = Game.getLocalPlayer();
	if (currentEntity == nullptr)
		return;

	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;

	if (!Game.getLocalPlayer()->isAlive())
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void Xp(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 69)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void TNT(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 65)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void ArmourStand(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 61)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void Minecart(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 84)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 255) {
		targetList.push_back(currentEntity);
	}
}

void NoEntityRender::onTick(GameMode* gm) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	targetList.clear();

	if (isBoat)
		Game.forEachEntity(boats);

	if (isFallingBlock)
		Game.forEachEntity(fallingblocks);

	if (isPainting)
		Game.forEachEntity(painting);

	if (isItems)
		Game.forEachEntity(Items);

	if (isPlayers)
		Game.forEachEntity(Players);

	if (isXp)
		Game.forEachEntity(Xp);

	if (isTNT)
		Game.forEachEntity(TNT);

	if (isArmourStand)
		Game.forEachEntity(ArmourStand);

	if (isMinecart)
		Game.forEachEntity(Minecart);

	if (!targetList.empty()) {
		for (auto& i : targetList) {
			i->despawn();
		}
	}
}