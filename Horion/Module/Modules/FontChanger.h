#pragma once
#include "Module.h"

class FontChanger : public IModule {
public:
	SettingEnum Fonts = SettingEnum(this);
	FontChanger();
	~FontChanger();

	// Inherited via IModule
	virtual const char* getModuleName() override;
};