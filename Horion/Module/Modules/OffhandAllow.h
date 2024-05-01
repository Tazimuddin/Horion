#pragma once

#include "Module.h"

class OffhandAllow : public IModule {
public:
	OffhandAllow();
	~OffhandAllow();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
};