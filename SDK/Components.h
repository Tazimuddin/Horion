#pragma once

#include "../Utils/HMath.h"

#include "GameType.h"
#include "PlayerMovementProxy.h"

struct MobBodyRotationComponent {
	float bodyRot;
	float prevBodyRot;
};

struct ActorRotationComponent {
	Vec2 rot;
	Vec2 rotPrev;
};

struct ActorHeadRotationComponent {
	Vec2 rot;
};

struct RuntimeIDComponent {
	int64_t runtimeID;
};

struct MaxAutoStepComponent {
	float stepHeight;
};

struct FallDistanceComponent {
	float fallDistance;
};

class PlayerMovementProxy;

struct ActorMovementProxyComponent {
	PlayerMovementProxy* movementProxy;
};

struct BlockSourceComponent {
	BlockSource* region;
};

struct ActorGameTypeComponent {
	enum GameType gameType;
};

struct RenderPositionComponent {
public:
	Vec3 renderPos;
};

struct AABBShapeComponent {
public:
	AABB aabb;
};
