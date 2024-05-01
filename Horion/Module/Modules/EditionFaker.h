#pragma once

#include "Module.h"

class EditionFaker : public IModule {
public:
	SettingEnum edition = SettingEnum(this);
	
	EditionFaker();
	~EditionFaker();

	int getFakedEditon();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
