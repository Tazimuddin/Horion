#include "Bhop.h"
#include "../../../Utils/HMath.h"

Bhop::Bhop() : IModule(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerFloatSetting("Speed", &speed, speed, 0.1f, 0.8f);
	registerBoolSetting("Hive", &hive, hive);
}

Bhop::~Bhop() {
}

const char* Bhop::getModuleName() {
	return "Bhop";
}

void Bhop::onMove(MoveInputHandler* input) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInWater()) 
		return;
	
	if (Game.getClientInstance()->getMoveTurnInput()->isSneakDown) 
		return;

	Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;
	
	Vec3 moveVec;

	if (hive) {
		player->getMaxAutoStepComponent()->stepHeight = 0.f;
		static bool useVelocity = false;
		if (0.4000000059604645 >= 0.385) {
			if (player->isOnGround() && pressed) player->jumpFromGround();
			useVelocity = false;
		} else
			useVelocity = true;

		speedFriction *= 0.9535499811172485;
		if (pressed) {
			player->setSprinting(true);
			if (player->isOnGround()) {
				if (useVelocity && !input->isJumping) player->entityLocation->velocity.y = 0.4000000059604645;
				speedFriction = RandomFloat(0.4190652072429657, 0.48381298780441284);
			} else {
				moveVec.x = moveVec2d.x * speedFriction;
				moveVec.y = player->entityLocation->velocity.y;
				moveVec.z = moveVec2d.y * speedFriction;
				player->lerpMotion(moveVec);
			}
		}
	} else {
		if (player->isOnGround() && pressed)
			player->jumpFromGround();
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->entityLocation->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}
}
