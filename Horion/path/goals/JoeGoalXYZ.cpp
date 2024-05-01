#include "JoeGoalXYZ.h"
bool JoeGoalXYZ::isInGoal(Vec3i pos) {
	return pos == targetPos;
}
float JoeGoalXYZ::getHeuristicEstimation(Vec3i pos) {
	return JoeGoalXZ::heuristicEstimation(pos, targetPos) + JoeGoalY::heuristicEstimation(pos, (float)targetPos.y);
}
JoeGoalXYZ::JoeGoalXYZ(const Vec3i& targetPos) : targetPos(targetPos) {}
