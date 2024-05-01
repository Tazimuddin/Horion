#pragma once

#include "../../Utils/HMath.h"
#include <vector>

enum JoeSegmentType{
	INVALID = -1,
	WALK = 0,
	JUMP,
	DROP,
	PARKOUR_JUMP_SINGLE,
	WATER_WALK
};

class JoeSegment {
private:
	JoeSegmentType segmentType;
	Vec3i start, end;
	float cost;
	bool allowSprint;
	std::vector<Vec3i> validPositions;
public:
	JoeSegment(JoeSegmentType type, Vec3i& start, Vec3i& stop, float cost, bool allowSprint = false);
	void draw();
	bool isAllowingSprint() const;
	void setAllowSprint(bool allowSprint);
	JoeSegmentType getSegmentType() const;
	const Vec3i& getStart() const;
	const Vec3i& getEnd() const;
	bool isInValidPosition(const Vec3i& pos) const;
	void setValidPositions(const std::vector<Vec3i>& validPositions);
	float getCost() const;
	void init();
};
