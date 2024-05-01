#pragma once

#include "JoePath.h"
#include "../../SDK/Entity.h"
#include "../../SDK/MoveInputHandler.h"

class JoeMovementController {
private:
	std::shared_ptr<JoePath> currentPath;
	struct {
		int currentPathSegment = 0;
		bool recoverToStartPos = false;

		void nextSegment(){
			currentPathSegment++;
			recoverToStartPos = false;
		}
	} stateInfo;

public:
	bool overrideViewAngles = false;
	Vec2 targetViewAngles = {0, 0};

	JoeMovementController(std::shared_ptr<JoePath> path);

	void step(LocalPlayer* player, MoveInputHandler* movementHandler);
	bool isDone(){
		return stateInfo.currentPathSegment >= currentPath->getNumSegments();
	}
	int getCurrentPathSegment() const;
	const std::shared_ptr<JoePath>& getCurrentPath() const;
};
