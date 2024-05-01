#include "ConfigCommand.h"

ConfigCommand::ConfigCommand() : IMCCommand("config", "Load/save configs", "<load/new/save> <name>") {
	registerAlias("cfg");
	registerAlias("c");
}

ConfigCommand::~ConfigCommand() {
}

bool ConfigCommand::execute(std::vector<std::string>* args) {
	std::string option = args->at(1);
	if (option == "load" || option == "l") {
		std::string name = args->at(2);
		configMgr->loadConfig(name, false);
		return true;
	} else if (option == "new" || option == "n") {
		std::string name = args->at(2);
		configMgr->loadConfig(name, true);
		return true;
	} else if (option == "save" || option == "s") {
		configMgr->saveConfig();
		std::string configName = configMgr->currentConfig;
		clientMessageF("[%sHorion%s] %sSuccessfully saved config %s%s%s!", GOLD, WHITE, GREEN, GRAY, configName.c_str(), GREEN);
		return true;
	}
	return false;
}