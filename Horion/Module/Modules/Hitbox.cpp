#include "Hitbox.h"

Hitbox::Hitbox() : IModule(0, Category::COMBAT, "Increase an entitys hitbox size.") {
	registerFloatSetting("Height", &height, height, 1.8f, 10);
	registerFloatSetting("Width", &width, width, 0.6f, 10);
}

Hitbox::~Hitbox() {
}

const char* Hitbox::getModuleName() {
	return "Hitbox";
}

void findTarget(Entity* currentEntity, bool isRegularEntitie) {
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();
	
	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;

	if (currentEntity == 0)
		return;

	if (!currentEntity->isAlive() || currentEntity->damageTime >= 7)
		return;

	if (!Target::isValidTarget(currentEntity))
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < hitboxMod->range) {
		currentEntity->getAABBShapeComponent()->aabb.width = hitboxMod->width;
		currentEntity->getAABBShapeComponent()->aabb.height = hitboxMod->height;
	}
	
}

void Hitbox::onTick(GameMode* gm) {
	Game.forEachEntity(findTarget);
}
