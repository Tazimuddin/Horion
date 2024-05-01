#include "Entity.h"

#include "../Memory/GameData.h"
#include "../Utils/Utils.h"
InventoryTransactionManager *Entity::getTransactionManager() {
	/*static unsigned int offset = 0;
	if (offset == 0) {
		offset = *reinterpret_cast<int*>(FindSignature("49 8D 8E ? ? ? ? E8 ? ? ? ? 90 48 8D 8D ? ? ? ? E8 ? ? ? ? 49 8B 06 48 8B 95") + 3);
	}*/
	return reinterpret_cast<InventoryTransactionManager *>(reinterpret_cast<__int64>(this) + 0xEC8);
}
PlayerInventoryProxy *Player::getSupplies() {
	/*static unsigned int offset = 0;
	if (offset == 0) {
		offset = *reinterpret_cast<int *>(FindSignature("48 8B 51 ?? 4C 8B 82 ?? ?? ?? ?? 48 8B B2 ?? ?? ?? ?? 41 80 B8") + 7);  // GameMode::startDestroyBlock -> GameMode::_canDestroy -> getSupplies
	}*/
	return *reinterpret_cast<PlayerInventoryProxy **>(reinterpret_cast<__int64>(this) + 0x848);
}
int Player::getDeviceID() {
	/*static unsigned int offset = 0;
	if (offset == 0) {
		offset = *reinterpret_cast<int *>(FindSignature("8B 87 ? ? ? ? 89 83 ? ? ? ? 8B 87 ? ? ? ? 89 83 ? ? ? ? 4C 8D B3") + 3); // Player::getPlatform
	}*/
	return *reinterpret_cast<int*>(reinterpret_cast<__int64>(this) + 0x848);
}
void LocalPlayer::unlockAchievements() {  // MinecraftEventing::fireEventAwardAchievement
	using fireEventAward = void(__fastcall *)(void *, int);
	static fireEventAward fireEventAwardFunc = reinterpret_cast<fireEventAward>(FindSignature("48 85 C9 0F 84 ? ? ? ? 48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 01"));
	for (int i = 0; i < 118; i++)
		fireEventAwardFunc(this, i);
}
void LocalPlayer::applyTurnDelta(Vec2 *viewAngleDelta) {
	using applyTurnDelta = void(__thiscall *)(void *, Vec2 *);
	static applyTurnDelta TurnDelta = reinterpret_cast<applyTurnDelta>(FindSignature("48 8B C4 48 89 58 18 48 89 68 20 56 57 41 56 48 81 EC ?? ?? ?? ?? 0F 29 70 D8 0F 29 78 C8 44 0F 29 40 ?? 48 8B 05 ?? ?? ?? ??"));
	TurnDelta(this, viewAngleDelta);
}

bool Level::hasEntity() {
	return rayHitType == 1;
}

float Entity::getBlocksPerSecond() {
	return getTicksPerSecond() * *Game.getClientInstance()->minecraft->timer;
}

void Entity::lerpTo(Vec3 const &pos, Vec2 const &rot, int steps) { //lerpTo was removed from the Player vtable so this is how we are going to use it from now on
	using lerpTo = void(__fastcall *)(Entity *, Vec3 const &, Vec2 const &, int);
	static lerpTo lerp = reinterpret_cast<lerpTo>(FindSignature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 41 ? 48 8B F9 48 8B DA"));
	lerp(this, pos, rot, steps);
}

Entity *Level::getEntity() {
	if (rayHitType != 1) return nullptr;
	Entity *retval = nullptr;
	Game.forEachEntity([this, &retval](Entity *ent, bool b) {
		if (*(__int64 *)((__int64)ent + 0x10) == GamingEntityFinder) {
			retval = ent;
			return;
		}
	});
	return retval;
}