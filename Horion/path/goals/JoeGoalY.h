#pragma once

#include "JoeGoal.h"

class JoeGoalY : public JoeGoal {
private:
	float target;
public:
	JoeGoalY(float target);

	bool isInGoal(Vec3i pos) override;
	float getHeuristicEstimation(Vec3i pos) override;

	static float heuristicEstimation(Vec3i node, float target);
};
