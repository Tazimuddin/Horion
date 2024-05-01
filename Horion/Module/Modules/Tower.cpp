#include "Tower.h"

#include "../../DrawUtils.h"

Tower::Tower() : IModule(0, Category::WORLD, "Like scaffold, but vertically and a lot faster.") {
	registerFloatSetting("Motion", &motion, motion, 0.3f, 1.f);
}

Tower::~Tower() {
}

const char* Tower::getModuleName() {
	return "Tower";
}

bool Tower::tryTower(Vec3 blockBelow) {
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return false;

	blockBelow = blockBelow.floor();

	DrawUtils::drawBox(blockBelow, Vec3(blockBelow).add(1), 0.4f);

	Block* block = Game.getLocalPlayer()->getRegion()->getBlock(Vec3i(blockBelow));
	BlockLegacy* blockLegacy = (block->blockLegacy);
	if (blockLegacy->material->isReplaceable) {
		Vec3i blok(blockBelow);

		// Find neighbour
		static std::vector<Vec3i*> checklist;
		if (checklist.empty()) {
			checklist.push_back(new Vec3i(0, -1, 0));
			checklist.push_back(new Vec3i(0, 1, 0));

			checklist.push_back(new Vec3i(0, 0, -1));
			checklist.push_back(new Vec3i(0, 0, 1));

			checklist.push_back(new Vec3i(-1, 0, 0));
			checklist.push_back(new Vec3i(1, 0, 0));
		}
		bool foundCandidate = false;
		int i = 0;
		for (auto current : checklist) {
			Vec3i calc = blok.sub(*current);
			if (!((Game.getLocalPlayer()->region->getBlock(calc)->blockLegacy))->material->isReplaceable) {
				// Found a solid block to click
				foundCandidate = true;
				blok = calc;
				break;
			}
			i++;
		}
		if (foundCandidate && GameData::isKeyDown(*input->spaceBarKey)) {
			Vec3 moveVec;
			moveVec.x = Game.getLocalPlayer()->entityLocation->velocity.x;
			moveVec.y = motion;
			moveVec.z = Game.getLocalPlayer()->entityLocation->velocity.z;
			Game.getLocalPlayer()->lerpMotion(moveVec);
			bool idk = true;
			Game.getGameMode()->buildBlock(&blok, i, idk);

			return true;
		}
	}
	return false;
}

void Tower::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (Game.getLocalPlayer() == nullptr)
		return;
	if (!Game.canUseMoveKeys())
		return;
	auto selectedItem = Game.getLocalPlayer()->getSelectedItem();
	if (!selectedItem->isValid() || !(*selectedItem->item)->isBlock())  // Block in hand?
		return;

	Vec3 blockBelow = *Game.getLocalPlayer()->getPos();  // Block below the player
	blockBelow.y -= Game.getLocalPlayer()->getAABBShapeComponent()->aabb.height;
	blockBelow.y -= 0.5f;

	// Adjustment by velocity
	float speed = Game.getLocalPlayer()->entityLocation->velocity.magnitudexy();
	Vec3 vel = Game.getLocalPlayer()->entityLocation->velocity;
	vel.normalize();  // Only use values from 0 - 1

	if (!tryTower(blockBelow)) {
		if (speed > 0.05f) {
			blockBelow.z -= vel.z * 0.4f;
			if (!tryTower(blockBelow)) {
				blockBelow.x -= vel.x * 0.4f;
				if (!tryTower(blockBelow) && Game.getLocalPlayer()->isSprinting()) {
					blockBelow.z += vel.z;
					blockBelow.x += vel.x;
					tryTower(blockBelow);
				}
			}
		}
	}
}
