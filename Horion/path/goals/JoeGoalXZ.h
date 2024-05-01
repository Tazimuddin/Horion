#pragma once

#include "JoeGoal.h"

class JoeGoalXZ : public JoeGoal{
private:
	Vec3i targetPos;
public:
	JoeGoalXZ(const Vec3i& targetPos);

	bool isInGoal(Vec3i pos) override;
	float getHeuristicEstimation(Vec3i pos) override;

	static float heuristicEstimation(Vec3i node, Vec3i target);
};
