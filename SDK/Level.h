#pragma once

#include <iostream>
#include <string>

#include "Entity.h"
#include "../Utils/HMath.h"
#include "../Utils/Utils.h"

class Level {
	char pad_0x0[0xBF0];

public:
	int rayHitType;
	int blockSide;
	Vec3i block;
	Vec3 rayHitVec;
	Entity *entityPtr;
	Entity *entityPtr2;
	uint64_t GamingEntityFinder;

	BUILD_ACCESS(this, int, levelTicks, 0x8A0);

public:
	bool hasEntity();     // to not go trough the entity list twice
	Entity *getEntity();  // returns the entity that the player is looking at
	int getLevelTicks() {
		// return levelTicks;
		return *reinterpret_cast<int *>(reinterpret_cast<__int64>(this) + 0x8A0);
	}

	class LoopbackPacketSender *getLoopbackPacketSender() {
		return *reinterpret_cast<class LoopbackPacketSender **>(reinterpret_cast<__int64>(this) + 0xBD8);
	}

	void playSound(std::string sound, Vec3 const &position, float volume, float pitch) {
		static uintptr_t sig = 0x0;

		if (sig == 0)
			sig = FindSignature("48 89 5C ? ? 48 89 6C ? ? 48 89 74 ? ? 57 48 83 EC ? 48 8B 41 ? 33 FF");

		using playSound_t = void(__fastcall *)(Level *, TextHolder *, Vec3 const &, float, float);
		static playSound_t func = reinterpret_cast<playSound_t>(sig);
		if (func != nullptr) func(this, &TextHolder(sound), position, volume, pitch);
	}

	// Credits to hacker hansen for this
	std::vector<Entity *> getMiscEntityList() {  // Level::getRuntimeActorList
		static uintptr_t sig = 0x0;

		if (sig == 0)
			sig = FindSignature("40 53 48 83 EC ? 48 81 C1 ? ? ? ? 48 8B DA E8 ? ? ? ? 48 8B C3 48 83 C4 ? 5B C3 CC CC 48 8B 81");

		using entityList_t = std::int64_t *(__fastcall *)(Level *, void *);
		static entityList_t func = reinterpret_cast<entityList_t>(sig);
		if (func != nullptr) {
			std::unique_ptr<char[]> alloc = std::make_unique<char[]>(0x18);
			std::int64_t *listStart = func(this, alloc.get());
			std::size_t listSize = ((*reinterpret_cast<std::int64_t *>(reinterpret_cast<std::int64_t>(listStart) + 0x8)) - (*listStart)) / 0x8;
			Entity **entityList = reinterpret_cast<Entity **>(*listStart);
			std::vector<Entity *> res;
			res.reserve(listSize);
			if (listSize > 0 && listSize < 5000) {
				for (std::size_t i = 0; i < listSize; i++) res.push_back(entityList[i]);
			}
			return res;
		}
		return {};
	}
};
