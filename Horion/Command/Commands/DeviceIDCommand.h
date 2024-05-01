#pragma once

#include "ICommand.h"

class DeviceIDCommand : public IMCCommand {
public:
	DeviceIDCommand();
	~DeviceIDCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
