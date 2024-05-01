#pragma once

#include "../../../Utils/HMath.h"

class JoeGoal {
private:
public:
	virtual ~JoeGoal();

	virtual bool isInGoal(Vec3i pos) = 0;
	virtual float getHeuristicEstimation(Vec3i pos) = 0;
};
