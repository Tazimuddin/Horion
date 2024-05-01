#pragma once
#include "Module.h"
class Scaffold : public IModule {
private:
	bool autoSelect = false;
	bool down = false;
	bool highlight = true;
	bool hive = false;
	bool rotations = true;
	int extend = 0;
	bool Ylock = false;
	bool tryScaffold(Vec3 blockBelow);
	bool tryClutchScaffold(Vec3 blockBelow);
	bool findBlock();
	float YCoord;

public:
	Scaffold();
	~Scaffold(){};

	void handleScaffoldDown(Player* player, float speed, const Vec3& velocity);
	void handleScaffoldUp(Player* player, float speed, const Vec3& velocity);
	Vec3 getBlockBelow(Player* player, float yOffset);
	void adjustYCoordinate(Vec3& blockBelow, const Vec3& blockBelowReal);
	void extendBlock(Player* player, const Vec3& velocity, Vec3& blockBelow);
	void attemptScaffoldWhileMoving(Player* player, float speed, const Vec3& velocity, Vec3& blockBelow, Vec3& blockBelowBelow);
	void handleReplaceableBlock(Player* player, float speed, const Vec3& velocity, Vec3& blockBelow);
	void handleNonReplaceableBlock(Player* player, float speed, const Vec3& velocity, Vec3& blockBelow);
	Vec3 getNextBlock(Player* player, const Vec3& velocity, const Vec3& blockBelow);

	virtual const char* getModuleName() {
		return "Scaffold";
	};
	virtual void onEnable() {
		auto player = Game.getLocalPlayer();
		if (player == nullptr) return;
		float yPos = player->getPos()->y;  // Block 1 block below the player
		yPos -= player->getAABBShapeComponent()->aabb.height;
		yPos -= 0.5f;
		YCoord = yPos;
	};
	virtual void onPostRender(MinecraftUIRenderContext* ctx) override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onPlayerTick(Player* player) override;
};
