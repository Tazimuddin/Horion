#include "CommandMgr.h"
#include "../../Utils/Logger.h"

CommandMgr::CommandMgr(GameData* gm) {
	gameData = gm;
}

CommandMgr::~CommandMgr() {
	for (int i = 0; i < commandList.size(); i++) {
		delete commandList[i];
		commandList[i] = nullptr;
	}
}

void CommandMgr::initCommands() {
	logF("Initializing commands");

	commandList.push_back(new CommandBlockExploitCommand());
	commandList.push_back(new RelativeTeleportCommand());
	commandList.push_back(new PlayerTeleportCommand());
	commandList.push_back(new SetOffhandCommand());
	commandList.push_back(new FriendListCommand());
	commandList.push_back(new NameSpoofCommand());
	commandList.push_back(new SetPrefixCommand());
	commandList.push_back(new WaypointCommand());
	commandList.push_back(new GameModeCommand());
	commandList.push_back(new TeleportCommand());
	commandList.push_back(new DeviceIDCommand());
	commandList.push_back(new SpammerCommand());
	commandList.push_back(new ModulesCommand());
	commandList.push_back(new EnchantCommand());
	commandList.push_back(new SetLoreCommand());
	commandList.push_back(new ConfigCommand());
	commandList.push_back(new DamageCommand());
	commandList.push_back(new CoordsCommand());
	commandList.push_back(new ServerCommand());
	commandList.push_back(new UnbindCommand());
	commandList.push_back(new ToggleCommand());
	commandList.push_back(new RenameCommand());
	commandList.push_back(new RepairCommand());
	commandList.push_back(new PanicCommand());
	commandList.push_back(new EjectCommand());
	commandList.push_back(new PathCommand());
	commandList.push_back(new DupeCommand());
	commandList.push_back(new BruhCommand());
	commandList.push_back(new GiveCommand());
	commandList.push_back(new HideCommand());
	commandList.push_back(new HelpCommand());
	commandList.push_back(new BindCommand());
	commandList.push_back(new SeedCommand());
	commandList.push_back(new TopCommand());
	commandList.push_back(new NbtCommand());
	commandList.push_back(new SayCommand());
	commandList.push_back(new XpCommand());

#ifdef _DEBUG
	commandList.push_back(new TestCommand());
#endif
}

void CommandMgr::disable() {
}

std::vector<IMCCommand*>* CommandMgr::getCommandList() {
	return &commandList;
}

void CommandMgr::execute(char* message) {
	if (message == nullptr) {
		return;
	}

	std::vector<std::string> args;
	std::string msgStr = message + 1;
	size_t pos = msgStr.find(" "), initialPos = 0;
	while (pos != std::string::npos) {
		args.push_back(msgStr.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;
		pos = msgStr.find(" ", initialPos);
	}
	args.push_back(msgStr.substr(initialPos, std::min(pos, msgStr.size()) - initialPos + 1));
	std::string cmd = args[0];
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

	for (auto& c : commandList) {
		auto aliases = c->getAliasList();
		for (const auto& alias : *aliases) {
			if (alias == cmd) {
				try {
					if (!c->execute(&args)) {
						Game.getGuiData()->displayClientMessageF("%s%sUsage: %s%c%s %s", RED, BOLD, RESET, cmdMgr->prefix, c->getCommand(), c->getUsage(cmd.c_str()));
					}
				} catch (...) {
					Game.getGuiData()->displayClientMessageF("%s%sUsage: %s%c%s %s", RED, BOLD, RESET, cmdMgr->prefix, c->getCommand(), c->getUsage(cmd.c_str()));
				}
				return;
			}
		}
	}

	// If the command doesn't exist, display an error message
	Game.getGuiData()->displayClientMessageF("[%sHorion%s] %sCommand '%s' could not be found!", GOLD, WHITE, RED, cmd.c_str());
	// Loop through all commands
	for (auto it = this->commandList.begin(); it != this->commandList.end(); ++it) {
		IMCCommand* c = *it;
		std::string commandCopy = c->getCommand();

		// Put them both in lowercase so they can be compaired
		std::transform(commandCopy.begin(), commandCopy.end(), commandCopy.begin(), ::tolower);
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

		if (commandCopy.find(cmd) != std::string::npos)                                                 // if it has the name in it but not completed
			Game.getGuiData()->displayClientMessageF("%sDid you mean to type: %s?", RED, commandCopy.c_str());  // Tell the user what they might have ment
	}
}

CommandMgr* cmdMgr = new CommandMgr(&Game);