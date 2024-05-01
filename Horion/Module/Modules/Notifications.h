#pragma once
#include "Module.h"
class Notifications : public IModule {
public:
	Notifications();
	~Notifications();

	virtual const char* getModuleName() override;
};