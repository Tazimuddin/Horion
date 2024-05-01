#include "AntiBot.h"

AntiBot::AntiBot() : IModule(0, Category::PLAYER, "Enable this module to filter out bots!") {
	registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
	//registerBoolSetting("Name Check", &nameCheck, nameCheck);
	registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
	registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
	registerBoolSetting("Other Check", &otherCheck, otherCheck);
	registerBoolSetting("Extra Check", &extraCheck, extraCheck);
	registerBoolSetting("Player Check", &playerCheck, playerCheck);
	registerBoolSetting("LifeboatFLY", &LifeboatFLY, LifeboatFLY);
}

AntiBot::~AntiBot() {
}

const char* AntiBot::getModuleName() {
	return "AntiBot";
}
