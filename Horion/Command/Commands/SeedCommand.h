#pragma once

#include "ICommand.h"

class SeedCommand : public IMCCommand {
public:
	SeedCommand();
	~SeedCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
