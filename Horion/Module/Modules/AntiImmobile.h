#pragma once

#include "Module.h"

class AntiImmobile : public IModule {
public:
	AntiImmobile();
	~AntiImmobile();

	// Inherited via IModule
	const char* getModuleName() override;
};
