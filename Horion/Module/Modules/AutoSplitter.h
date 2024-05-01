#pragma once

#include <iostream>
#include <vector>

#include "Module.h"

class AutoSplitter : public IModule {
private:
	int maxAmount = 32;
	int delay = 1;
	int ticks = 0;
	std::vector<int> queue;

public:
	AutoSplitter();
	~AutoSplitter();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
