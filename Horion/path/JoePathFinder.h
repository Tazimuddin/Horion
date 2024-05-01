#pragma once

#include "../../Utils/HMath.h"
#include "JoePath.h"
#include "JoeSegment.h"
#include "goals/JoeGoal.h"
#include "../../SDK/BlockLegacy.h"
#include "JoeConstants.h"
#include <memory>

class JoePathFinder {
private:
	Vec3i startPos;
	JoePath currentPath;
	BlockSource* region;
	std::shared_ptr<JoeGoal> goal;
public:
	bool terminateSearch = false;
	float pathSearchTimeout = 5.f;

	JoePathFinder(Vec3i start, BlockSource* reg, std::shared_ptr<JoeGoal> goal);

	JoePath findPath();
	const JoePath& getCurrentPath() const;
};
