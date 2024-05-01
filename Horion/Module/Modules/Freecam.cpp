#include "Freecam.h"
#include "../../../Utils/Utils.h"

Freecam::Freecam() : IModule('V', Category::MISC, "Move your camera without moving the player.") {
	registerFloatSetting("Speed", &speed, speed, 0.50f, 1.25f);
}

Freecam::~Freecam() {
}

const char* Freecam::getModuleName() {
	return "Freecam";
}

void* cameraAddr = (void*)FindSignature("f3 0f 11 43 ? f3 0f 10 44 24 ? f3 0f 11 43");

void Freecam::onEnable() {
	auto Player = Game.getLocalPlayer();
	if (cameraAddr != nullptr) NopBytes((BYTE*)((uintptr_t)cameraAddr), 33);

	if (Player != nullptr) initialViewAngles = Vec2(Player->getActorHeadRotationComponent()->rot.x, Player->getActorHeadRotationComponent()->rot.y);
}

void Freecam::onDisable() {
	if (cameraAddr != nullptr) PatchBytes((BYTE*)((uintptr_t)cameraAddr), (BYTE*)"\xF3\x0F\x11\x43\x40\xF3\x0F\x10\x44\x24\x2C\xF3\x0F\x11\x43\x44\xF3\x0F\x10\x44\x24\x30\xF3\x0F\x11\x43\x48\xF3\x0F\x10\x44\x24\x44", 33);
}

void Freecam::onPreRender(MinecraftUIRenderContext* rcx) {
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	auto Player = Game.getLocalPlayer();

	if (input == nullptr)
		return;

	if (Player == nullptr)
		return;
	//yaw = Player->bodyYaw;

	bool isForwardKeyDown = GameData::isKeyDown(*input->forwardKey);
	bool isBackKeyDown = GameData::isKeyDown(*input->backKey);
	bool isRightKeyDown = GameData::isKeyDown(*input->rightKey);
	bool isLeftKeyDown = GameData::isKeyDown(*input->leftKey);
	bool keyPressed = false;

	if (isForwardKeyDown) {
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

	if (isForwardKeyDown && isBackKeyDown) {
		return;
	}

	yaw = fmod(yaw, 360.0f);
	if (yaw < 0) {
		yaw += 360.0f;
	}

	float calcYaw = (yaw + 90) * (PI / 180);

	Vec3 moveVec;
	moveVec.x = cos(calcYaw) * speed;
	if (GameData::isKeyDown(*input->spaceBarKey)) camera->cameraPos.y += speed;
	else if (GameData::isKeyDown(*input->sneakKey)) camera->cameraPos.y -= speed;
	moveVec.y = 0.f;
	moveVec.z = sin(calcYaw) * speed;

	if (keyPressed && camera) {
		camera->cameraPos = camera->cameraPos.add(moveVec);
		keyPressed = false;
	}
}