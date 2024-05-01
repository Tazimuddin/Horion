#pragma once
#include <vcruntime_string.h>

#include "TextHolder.h"

class Attribute {
public:
	__int64 hash;
	__int64 hashedStringHash;
	class TextHolder attributeName;

private:
	char __padding[0x32];

public:
	Attribute() {
		memset(this, 0x0, sizeof(Attribute));
	}

	Attribute(__int64 hash) {
		memset(this, 0x0, sizeof(Attribute));
		this->hash = hash;
	}
};

class HealthAttribute : public Attribute {
public:
	HealthAttribute() { this->hash = 25769804032; }
};

class PlayerHungerAttribute : public Attribute {
public:
	PlayerHungerAttribute() { this->hash = 4294967552; }
};

class MovementAttribute : public Attribute {
public:
	MovementAttribute() { this->hash = 38654705921; }
};

class AbsorptionAttribute : public Attribute {
public:
	AbsorptionAttribute() { this->hash = 55834575105; }
};

class PlayerSaturationAttribute : public Attribute {
public:
	PlayerSaturationAttribute() { this->hash = 8589934848; }
};

class AttackDamageAttribute : public Attribute {
public:
	AttackDamageAttribute() { this->hash = 51539607553; }
};

class FollowRangeAttribute : public Attribute {
public:
	FollowRangeAttribute() { this->hash = 30064771073; }
};

class PlayerLevelAttribute : public Attribute {
public:
	PlayerLevelAttribute() { this->hash = 17179869440; }
};

class PlayerExperienceAttribute : public Attribute {
public:
	PlayerExperienceAttribute() { this->hash = 21474836736; }
};

class KnockbackResistanceAttribute : public Attribute {
public:
	KnockbackResistanceAttribute() { this->hash = 34359738369; }
};

class LuckAttribute : public Attribute {
public:
	LuckAttribute() { this->hash = 60129542401; }
};

class AttributeInstance {
private:
	char __padding[0x74];

public:
	float minimumValue;
	float maximumValue;
	float currentValue;

	~AttributeInstance();
	virtual void tick(void);
};