#include "InventoryMove.h"

InventoryMove::InventoryMove() : IModule(0, Category::MOVEMENT, "Move even when you have your inventory open.") {
}

InventoryMove::~InventoryMove() {
}

const char* InventoryMove::getModuleName() {
	return "InvMove";
}

void InventoryMove::onTick(GameMode* gm) {
	if (Game.getLocalPlayer()->canOpenContainerScreen())
		return;
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return;

	float speed = 0.325f;
	float yaw = gm->player->getActorHeadRotationComponent()->rot.y;

	if (GameData::isKeyDown(*input->spaceBarKey) && gm->player->isOnGround()) {
		gm->player->jumpFromGround();
	}

	bool isForwardKeyDown = GameData::isKeyDown(*input->forwardKey);
	bool isBackKeyDown = GameData::isKeyDown(*input->backKey);
	bool isRightKeyDown = GameData::isKeyDown(*input->rightKey);
	bool isLeftKeyDown = GameData::isKeyDown(*input->leftKey);

	if (isForwardKeyDown && isBackKeyDown) {
		return;
	} else if (isForwardKeyDown) {
		keyPressed = true;

		if (isRightKeyDown && !isLeftKeyDown) {
			yaw += 45.f;
		} else if (isLeftKeyDown && !isRightKeyDown) {
			yaw -= 45.f;
		}
	} else if (isBackKeyDown) {
		keyPressed = true;

		if (isRightKeyDown && !isLeftKeyDown) {
			yaw += 135.f;
		} else if (isLeftKeyDown && !isRightKeyDown) {
			yaw -= 135.f;
		} else {
			yaw += 180.f;
		}
	} else if (isRightKeyDown && !isLeftKeyDown) {
		keyPressed = true;
		yaw += 90.f;
	} else if (isLeftKeyDown && !isRightKeyDown) {
		keyPressed = true;
		yaw -= 90.f;
	}
	if (yaw >= 180)
		yaw -= 360.f;

	float calcYaw = (yaw + 90) * (PI / 180);
	//float calcPitch = (gm->player->pitch) * -(PI / 180);
	Vec3 moveVec;
	moveVec.x = cos(calcYaw) * speed;
	moveVec.y = gm->player->entityLocation->velocity.y;
	moveVec.z = sin(calcYaw) * speed;
	if (keyPressed) {
		gm->player->lerpMotion(moveVec);
		keyPressed = false;
	}
}
