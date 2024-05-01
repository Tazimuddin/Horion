#pragma once

#include "Module.h"

class Teleport : public IModule {
private:
	bool onlyHand = false;
	bool lerp = false;
	float lerpSpeed = 0.1f;
	bool hasClicked = false;
	bool shouldTP = false;
	Vec3 tpPos;

public:
	Teleport();
	~Teleport();

	// Inherited via IModule
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName() override;
};