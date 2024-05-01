#pragma once

#include "Module.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

class AntiBot : public IModule {
private:
	float opacity = 0.f;
	bool hitboxCheck = true;
	bool nameCheck = false;
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool otherCheck = true;
	bool extraCheck = false;
	bool playerCheck = true;
	bool LifeboatFLY = true;

public:
	AntiBot();
	~AntiBot();

	inline bool isHitboxCheckEnabled() {
		return hitboxCheck && isEnabled();
	}
	inline bool isNameCheckEnabled() {
		return false && isEnabled();
	}
	inline bool isInvisibleCheckEnabled() {
		return invisibleCheck && isEnabled();
	}
	inline bool isEntityIdCheckEnabled() {
		return entityIdCheck && isEnabled();
	}
	inline bool isOtherCheckEnabled() {
		return otherCheck && isEnabled();
	}
	inline bool isExtraCheckEnabled() {
		return extraCheck && isEnabled();
	}
	inline bool isPlayerCheckEnabled() {
		return playerCheck && isEnabled();
	}

	// Inherited via IModule
	virtual const char* getModuleName() override;
};
