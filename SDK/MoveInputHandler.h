#pragma once
#include "../Utils/Utils.h"
class PlayerAuthInputPacket;

class MoveInputHandler {
public:
	BUILD_ACCESS(this, bool, isSneakDownPrev, 0x0);
	BUILD_ACCESS(this, bool, isJumpingPrev, 0x6);
	BUILD_ACCESS(this, bool, isSprintingPrev, 0x7);
	BUILD_ACCESS(this, bool, forwardPrev, 0xA);
	BUILD_ACCESS(this, bool, backwardPrev, 0xB);
	BUILD_ACCESS(this, bool, leftPrev, 0xC);
	BUILD_ACCESS(this, bool, rightPrev, 0xD);
	BUILD_ACCESS(this, bool, isSneakDown, 0x20);
	BUILD_ACCESS(this, bool, isJumping, 0x26);
	BUILD_ACCESS(this, bool, isSprinting, 0x27);
	BUILD_ACCESS(this, bool, forward, 0x2A);
	BUILD_ACCESS(this, bool, backward, 0x2B);
	BUILD_ACCESS(this, bool, left, 0x2C);
	BUILD_ACCESS(this, bool, right, 0x2D);
	BUILD_ACCESS(this, float, sideMovement, 0x48);
	BUILD_ACCESS(this, float, forwardMovement, 0x4C);

	bool isPressed() {
		return forward || backward || left || right;
	}
};
