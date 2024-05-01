#include "Target.h"

#include <regex>
#include "../Horion/FriendList/FriendsManager.h"

#include "../Horion/Module/ModuleManager.h"

LocalPlayer** localPlayer;

void Target::init(LocalPlayer** cl) {
	localPlayer = cl;
}

bool Target::isValidTarget(Entity* ent) {
	if (ent == nullptr)
		return false;

	auto localPlayer = Game.getLocalPlayer();

	if (ent == localPlayer)
		return false;

	static auto antibot = moduleMgr->getModule<AntiBot>();
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();
	static auto teams = moduleMgr->getModule<Teams>();
	static auto noFriends = moduleMgr->getModule<NoFriends>();

	if (!Game.isInGame())
		return false;
	if (!ent->isAlive())
		return false;

	auto entityTypeId = ent->getEntityTypeId();

	if (antibot->isEntityIdCheckEnabled() && entityTypeId <= 130 && entityTypeId != 63)
		return false;

	if (ent->isPlayer()) {
		if (teams->isColorCheckEnabled()) {
			std::string targetName = ent->getNameTag()->getText();
			std::string localName = localPlayer->getNameTag()->getText();

			if (targetName.size() > 2 && localName.size() > 2) {
				targetName = std::string(targetName, 0, targetName.find('\n'));
				localName = std::string(localName, 0, localName.find('\n'));

				std::string colorTargetName = std::regex_replace(targetName, std::regex(u8"§r"), "");
				std::string colorLocalName = std::regex_replace(localName, std::regex(u8"§r"), "");
				char colorTarget = colorTargetName[colorTargetName.find(u8"§") + 2];
				char colorLocal = colorLocalName[colorLocalName.find(u8"§") + 2];

				if (colorLocal == colorTarget)
					return false;
			}

			/*
			auto targetName = ent->getNameTag();
			auto localName = localPlayer->getNameTag();
			if (targetName->getTextLength() > 2 && localName->getTextLength() > 2) {
				auto colorTargetName = std::regex_replace(targetName->getText(), std::regex("\\§r"), "");
				auto colorLocalName = std::regex_replace(localName->getText(), std::regex("\\§r"), "");
				if (colorTargetName.at(0) == colorLocalName.at(0))
					return false;
			}
			*/
		}
		if (teams->isAlliedCheckEnabled()) {
			if (localPlayer->isAlliedTo(ent)) return false;
		}
	}

	// Temporarily removed from gui, tons of false negatives
	if (antibot->isNameCheckEnabled() && !Target::containsOnlyASCII(ent->getNameTag()->getText()))
		return false;

	if (!noFriends->isEnabled() && FriendsManager::findFriend(ent->getNameTag()->getText()))
		return false;

	if (antibot->isInvisibleCheckEnabled() && ent->isInvisible())
		return false;

	if (antibot->isOtherCheckEnabled() && (ent->isSilent() || ent->getNameTag()->getTextLength() < 1 || std::string(ent->getNameTag()->getText()).find(std::string("\n")) != std::string::npos))
		return false;

	if (!hitboxMod->isEnabled() && antibot->isHitboxCheckEnabled())
		if ((ent->getAABBShapeComponent()->aabb.height < 1.5f || ent->getAABBShapeComponent()->aabb.width < 0.49f || ent->getAABBShapeComponent()->aabb.height > 2.1f || ent->getAABBShapeComponent()->aabb.width > 0.9f))
			return false;

	if (!localPlayer->canAttack(ent, false))
		return false;

	if (antibot->isExtraCheckEnabled() && !ent->canShowNameTag())
		return false;

	if (antibot->isPlayerCheckEnabled() && !ent->isPlayer())
		return false;

	return true;
}

bool Target::containsOnlyASCII(const std::string& string) {
	for (auto c : string) {
		int n = static_cast<unsigned char>(c);
		if (n > 127 && n != -89) {
			return false;
		}
	}
	return true;
}
