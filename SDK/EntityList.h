#pragma once

#include "../Utils/HMath.h"
class Entity;

class EntityList {
private:
	char pad_0x0000[0x70];  //0x0000
public:
	uintptr_t firstEntity;  //0x0050
	uintptr_t lastEntity;   //0x0058
	uintptr_t endAddr;      //0x0060

	inline size_t getListSize() {
		return (lastEntity - firstEntity) / sizeof(uintptr_t);
	}

	inline Entity* get(size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<Entity**>(firstEntity + (idx * sizeof(uintptr_t)));
	}

	Entity* operator[](size_t idx) {
		return get(idx);
	}
};  //Size=0x0050

class MobEntityList {
public:
private:
	char pad_0x0000[0x38];  //0x0000
public:
	uintptr_t firstEntity;  //0x0038
	uintptr_t lastEntity;   //0x0040
	uintptr_t endAddr;      //0x0048

	inline size_t getListSize() {
		return (lastEntity - firstEntity) / sizeof(uintptr_t);
	}

	inline Entity* get(size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<Entity**>(firstEntity + (idx * sizeof(uintptr_t)));
	}

	Entity* operator[](size_t idx) {
		return get(idx);
	}
};  //Size=0x0050