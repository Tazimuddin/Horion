#include "ServerCommand.h"

ServerCommand::ServerCommand() : IMCCommand("server", "Show information about the server you're playing on", "") {
	registerAlias("ip");
}

ServerCommand::~ServerCommand() {
}

bool ServerCommand::execute(std::vector<std::string>* args) {
	assertTrue(Game.getLocalPlayer() != nullptr);

	if (Game.getRakNetConnector()->isonaServer()) {
		clientMessageF("You're currently playing on:\nIP: %s\nPort: %s", Game.getRakNetConnector()->serverIp.getText(), std::to_string(Game.getRakNetConnector()->serverPort).c_str());
	} else {
		clientMessageF("%sYou're not playing on a server.", RED);
	}
	return true;
}
