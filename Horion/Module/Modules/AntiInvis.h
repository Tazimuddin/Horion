#pragma once

#include "Module.h"

class AntiInvis : public IModule {
public:
	AntiInvis();
	~AntiInvis();

	// Inherited from IModule
	virtual const char* getModuleName() override;
};
