#pragma once

#include "Module.h"

class Nbt : public IModule {
private:
	std::string lastCopy;

public:
	Nbt();
	~Nbt();

	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
