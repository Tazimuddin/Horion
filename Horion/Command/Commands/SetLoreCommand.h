#pragma once

#include "ICommand.h"

class SetLoreCommand : public IMCCommand {
public:
	SetLoreCommand();
	~SetLoreCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
