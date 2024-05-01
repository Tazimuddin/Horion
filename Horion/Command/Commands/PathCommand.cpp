#include "PathCommand.h"

#include "../../Module/ModuleManager.h"
#include "../../path/goals/JoeGoalY.h"
#include "../../path/goals/JoeGoalXZ.h"
#include "../../path/goals/JoeGoalXYZ.h"

PathCommand::PathCommand() : IMCCommand("path", "Joe path", "<y|xz|xyz> [args]"){
	registerAlias("joe");
}
PathCommand::~PathCommand() {
}

bool PathCommand::execute(std::vector<std::string>* args) {
	assertTrue(args->size() > 1);
	static auto mod = moduleMgr->getModule<FollowPathModule>();

	if (mod->isEnabled()) {
		clientMessageF("Joe is already enabled, disable Joe to use this command");
		return true;
	}

	auto cmd = args->at(1);

	if (cmd == "y") {
		assertTrue(args->size() > 2);
		int yLevel = assertInt(args->at(2));
		assertTrue(yLevel > 0 && yLevel < 256);

		mod->goal = std::make_unique<JoeGoalY>(static_cast<float>(yLevel));
		mod->setEnabled(true);

		clientMessageF("Starting search...");
		return true;
	}

	if (cmd == "xz") {
		assertTrue(args->size() > 3);
		int x = assertInt(args->at(2));
		int z = assertInt(args->at(3));

		mod->goal = std::make_unique<JoeGoalXZ>(Vec3i(x, 0, z));
		mod->setEnabled(true);

		clientMessageF("Starting search...");
		return true;
	}

	if (cmd == "xyz") {
		assertTrue(args->size() > 4);
		int x = assertInt(args->at(2));
		int y = assertInt(args->at(3));
		int z = assertInt(args->at(4));

		mod->goal = std::make_unique<JoeGoalXYZ>(Vec3i(x, y, z));
		mod->setEnabled(true);

		clientMessageF("Starting search...");
		return true;
	}

	if (cmd == "p" || cmd == "player") {
		std::string nameOfPlayer = args->at(2);
		assertTrue(!nameOfPlayer.empty());
		std::string nameOfPlayerLower = nameOfPlayer;
		std::transform(nameOfPlayerLower.begin(), nameOfPlayerLower.end(), nameOfPlayerLower.begin(), ::tolower);
		nameOfPlayerLower = Utils::sanitize(nameOfPlayerLower);

		Vec3 pos{};
		auto playerFinder = [&](Entity* e, bool isNewList) {
			if (e == Game.getLocalPlayer())
				return;
			std::string name(e->getNameTag()->getText());
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);

			if (name.find(nameOfPlayerLower) == std::string::npos)
				return;

			pos = e->getRenderPositionComponent()->renderPos;
		};
		Game.forEachEntity(playerFinder);

		if (pos.iszero()) {
			clientMessageF("%s Player \"%s\" could not be found!", GOLD, nameOfPlayer.c_str());
			return true;
		}

		Vec3i endNode((int)floorf(pos.x), (int)roundf(pos.y - 1.62f), (int)floorf(pos.z));
		mod->goal = std::make_unique<JoeGoalXYZ>(endNode);
		mod->setEnabled(true);
		clientMessageF("Starting search...");

		return true;
	}

	return false;
}