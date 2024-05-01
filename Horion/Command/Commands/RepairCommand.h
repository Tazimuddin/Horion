#pragma once

#include "ICommand.h"

class RepairCommand : public IMCCommand {
public:
	RepairCommand();
	~RepairCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
