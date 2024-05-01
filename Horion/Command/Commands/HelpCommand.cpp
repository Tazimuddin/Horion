#include "HelpCommand.h"

#include "../CommandMgr.h"

HelpCommand::HelpCommand() : IMCCommand("help", "Lists all commands", "") {
	registerAlias("h");
}

HelpCommand::~HelpCommand() {
}

bool HelpCommand::execute(std::vector<std::string>* args) {
	clientMessageF("==========");
	std::vector<IMCCommand*>* commandList = cmdMgr->getCommandList();

	for (auto it = commandList->begin(); it != commandList->end(); ++it) {
		IMCCommand* command = *it;
		clientMessageF("%s%s - %s%s", command->getCommand(), GRAY, ITALIC, command->getDescription());
	}

	return true;
}
