#include "TeleportCommand.h"

#include "../../Module/Modules/Blink.h"
#include "../../Module/Modules/Timer.h"

TeleportCommand::TeleportCommand() : IMCCommand("tp", "Teleports to coordinates", "<X> <Y> <Z>") {
	registerAlias("teleport");
	registerAlias("setpos");
}

TeleportCommand::~TeleportCommand() {
	getMovePlayerPacketHolder()->clear();
	getPlayerAuthInputPacketHolder()->clear();
}

void TeleportCommand::onTick(GameMode* gm) {
	int timer = 150;
	Game.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
}

bool TeleportCommand::execute(std::vector<std::string>* args) {
	assertTrue(Game.getLocalPlayer() != nullptr);
	assertTrue(args->size() >= 4);

	Vec3 pos;
	pos.x = assertFloat(args->at(1));
	pos.y = assertFloat(args->at(2)) + 2;
	pos.z = assertFloat(args->at(3));

	bool lerp = true;
	float lerpSpeed = 0.086f;
	float lerpSpeedVertical = 0.1f;

	bool useBlink = false;
	float blinkDistance = 50.f;

	int timer2 = 150;
	Game.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer2));

	if (lerp) {
		Vec3* playerPos = Game.getLocalPlayer()->getPos();

		if (useBlink && playerPos->dist(pos) > blinkDistance) {
			return true;
		} else {
			float verticalDistance = std::abs(pos.y - playerPos->y);

			if (pos.y > playerPos->y) {
				lerpSpeed = lerpSpeedVertical;
			} else if (pos.y < playerPos->y) {
				lerpSpeed += lerpSpeedVertical;
			} else {
				lerpSpeed += 0.086f;
			}

			Game.getLocalPlayer()->lerpTo(pos, Vec2(1, 1), (int)std::fmax((int)(playerPos->dist(pos) * lerpSpeed), 1));
			;
		}
	} else {
		Game.getLocalPlayer()->setPos(pos);
	}

	Game.getGuiData()->displayClientMessageF("%sTeleport position set to %sX: %.1f Y: %.1f Z: %.1f%s.", DARK_PURPLE, GRAY, pos.x, pos.y, pos.z, GREEN);
	return true;
}
