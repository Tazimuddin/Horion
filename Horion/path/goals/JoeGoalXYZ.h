#pragma once

#include "JoeGoal.h"
#include "JoeGoalY.h"
#include "JoeGoalXZ.h"

class JoeGoalXYZ : public JoeGoal {
private:
	Vec3i targetPos;
public:
	JoeGoalXYZ(const Vec3i& targetPos);

	bool isInGoal(Vec3i pos) override;
	float getHeuristicEstimation(Vec3i pos) override;
};
