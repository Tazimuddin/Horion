#pragma once

#include "ICommand.h"

class RenameCommand : public IMCCommand {
public:
	RenameCommand();
	~RenameCommand();

	// Inherited via IMCCommand
	virtual bool execute(std::vector<std::string>* args) override;
};
