#pragma once
#include "../Utils/HMath.h"
#include "ComplexInventoryTransaction.h"
#include "Entity.h"
#include "TextHolder.h"

class Packet {
public:
	uintptr_t** vTable;  //0x0000
private:
	char pad_0x8[0x28];
public:
	TextHolder* getName();
	template <class T>
	bool isInstanceOf() {
		T packet;
		if (packet.vTable == this->vTable)
			return true;
		else
			return false;
	}
};

class LevelSoundEventPacket : public Packet {
public:
	int sound;           //0x28
	Vec3 pos;          //0x2C
	int extraData = -1;  //0x38
private:
	int unknown = 0;  //0x3C
public:
	TextHolder entityType;               //0x40
	bool isBabyMod = false;              //0x60
	bool disableRelativeVolume = false;  //0x61
	LevelSoundEventPacket();
};

class PlayerAuthInputPacket : public Packet {
public:
	//uint64_t entityRuntimeId; //0x0020
	float pitch;  //0x0028
	float yaw;
	Vec3 pos;       //0x0030
	float yawUnused;  //0x0038
	Vec3 velocity;
	float InputAD;  // 1 for A, -1 for D, multiply by sqrt(2)/2 if mixed with InputWS
	float InputWS;  // 1 for W, -1 for S, multiply by sqrt(2)/2 if mixed with InputAD
private:
	uint8_t padshit[12];
public:
	uint32_t inputKeys;
	char padding[0x256];

public:
	PlayerAuthInputPacket();
	PlayerAuthInputPacket(Vec3 pos, float pitch, float yaw, float yawUnused);
};

class PlayerActionPacket : public Packet {
public:
	PlayerActionPacket();
	
	Vec3i blockPosition;    // 0x28
	int face;                 // 0x34
	int action;               // 0x38
	__int64 entityRuntimeId;  // 0x40
};

class SubChunkRequestPacket : public Packet {
public:
	SubChunkRequestPacket();
};

class EmotePacket : public Packet {
public:
	EmotePacket();

private:
	char padding[0x28];

public:
	int64_t entityRuntimeId;
	TextHolder emotId;
	char flags;
};

class AnimatePacket : public Packet {
public:
	AnimatePacket();
	AnimatePacket(int action, __int64 entityRuntimeID, float rowingTime);

	__int64 entityId;
	int action;
	float rowingTime;
};

class NPCRequestPacket : public Packet {
public:
	NPCRequestPacket();
	
	long entityRuntimeId;  //Test
	__int64 Unknown0;      //Test
	std::string Unknown1;  //Test
	__int64 Unknown2;      //Test
};

class PlayerSkinPacket : public Packet {
public:
	PlayerSkinPacket();
	
	__int64 UUID;
	__int64 skin;  //meant to be skin class
	std::string skinName;
	std::string oldSkinName;
};

class NetworkLatencyPacket : public Packet {
public:
	NetworkLatencyPacket();
	
	unsigned long timeStamp;  //Test
	bool sendBack;            //Test
	int pad[0x100];           //0x0
};

class CommandRequestPacket : public Packet {
public:
	CommandRequestPacket();
	CommandRequestPacket(std::string cmd);
	
	enum class Origin {
		PLAYER = 0,
		COMMAND_BLOCK = 1,
		MINECART_COMMAND_BLOCK = 2,
		DEV_CONSOLE = 3,
		AUTOMATION_PLAYER = 4,
		CLIENT_AUTOMATION = 5,
		DEDICATED_SERVER = 6,
		ENTITY = 7,
		VIRTUAL = 8,
		GAME_ARGUMENT = 9,
		INTERNAL = 10
	};

	TextHolder command;
	Origin origin = Origin::PLAYER;
	bool isExternal = 0;
	char shit[0x256];
};

class InteractPacket : public Packet {
public:
	InteractPacket(/**enum InteractPacket::Action, class ActorRuntimeID, Vec3 const&*/);
	
public:
	int action;
	long target;
};

class SetPlayerGameTypePacket : public Packet {
public:
	SetPlayerGameTypePacket();

public:
	int gameMode;
};

class ActorEventPacket : public Packet {
public:
	ActorEventPacket();
	ActorEventPacket(uint64_t entityRuntimeId, char eventId, int16_t itemId);
	
	uint64_t entityRuntimeId;  //0x0030
	char eventId;              //0x0038
	char pad_0x39[0x5];        //0x0039
	int16_t itemId;            //0x003E
};

class MobEquipmentPacket : public Packet {
public:
	MobEquipmentPacket();
	MobEquipmentPacket(__int64 entityRuntimeId, ItemStack& item, int hotbarSlot, int inventorySlot);

private:
	char pad_0x8[0x28];  // 0x0
public:
	__int64 entityRuntimeId;  // 0x28
	ItemStack item;         // 0x30
	int inventorySlot;        // 0xB8 DONT USE FOR PACKET SENDING
	int hotbarSlot;           // 0xBC DONT USE FOR PACKET SENDING
	char windowId;            // 0xC0  DONT USE FOR PACKET SENDING
	char windowId1;           // 0xC1  DONT USE FOR PACKET SENDING
	char inventorySlot1;      // 0xC2
	char hotbarSlot1;         // 0xC3
	char windowId2;           // 0xC4 ALL OF THIS IS PROBABLY BROKEN, DONT USE
	char unknown1;
};

class InventoryTransactionPacket : public Packet {
public:
	InventoryTransactionPacket();
	InventoryTransactionPacket(ComplexInventoryTransaction* transac) : InventoryTransactionPacket() {
		this->complexTransaction = transac;
	}
	
	int unknown = 0;                                    //0x28
	__int64* unknownStart = 0;                          //0x30
	__int64* unknownEnd = 0;                            //0x38
	__int64 filler = 0;                                 // 0x40
	ComplexInventoryTransaction* complexTransaction;  // 0x48
	unsigned char numTransactions;                      // 0x50
};

class TextPacket : public Packet {
public:
	TextPacket();

	unsigned __int8 messageType;  // 0x28

	unsigned char gap[7];

	TextHolder sourceName;           // 0x30
	TextHolder message;              // 0x50
	unsigned char field_24222[24];   // 0x70
	bool translationNeeded = false;  // 0x88

	unsigned char ga2p[7];  // 0x89
	TextHolder xboxUserId;
	TextHolder platformChatId;
};

class BookEditPacket : public Packet {
public:
	BookEditPacket();

	char action; // 0x28

private:
	char pad2[0x3]; // 0x29

public:
	char slot; // 0x2C

private:
	char pad3[0x3]; // 0x2D

public:
	char page; // 0x30

private:
	char pad4[0x3]; // 0x31

public:
	char secondaryPage; // 0x34

private:
	char pad5[0x3]; // 0x35

public:
	TextHolder title; // 0x38   Also used as Text
	TextHolder author; // 0x58   Also used as Photo name
	TextHolder xuid; // 0x78
};

class DisconnectPacket : public Packet {
public:
	DisconnectPacket();
	DisconnectPacket(TextHolder reason, bool hideDisconnectScreen);

	bool hideDisconnectScreen; // 0x28

private:
	char pad2[0xF]; // 0x29

public:
	TextHolder reason; // 0x38
};

class ResourcePacksInfoPacket : public Packet {
public:
	ResourcePacksInfoPacket();

	bool mustAccept; // 0x28
	bool scripting; // 0x29

private:
	char pad2[0x1]; // 0x2A

public:
	bool forceServerPacks; // 0x2B
};

#pragma pack(push, 8)

__declspec(align(8)) class MovePlayerPacket : public Packet {
public:
	MovePlayerPacket();
	MovePlayerPacket(LocalPlayer* player, Vec3 pos);
	
	__int64 entityRuntimeID;  //0x28
	Vec3 Position;          //0x30
	float pitch;              //0x3c
	float yaw;                //0x40
	float headYaw;            //0x44
	uint8_t mode;             //0x48
	bool onGround;
	__int64 ridingEid;
	int int1;
	int int2;
};

#pragma pack(pop)

class PlayerHotbarPacket : public Packet {
public:
	PlayerHotbarPacket();
	PlayerHotbarPacket(int selectedHotbarSlot, char containerId, bool selectHotbarSlot);

	int selectedHotbarSlot;
	char containerId;
	bool selectHotbarSlot;
};

class MobEffectPacket : public Packet {
public:
	MobEffectPacket();
	MobEffectPacket(__int64 entityRuntimeId, char event, int effectId, int amplifier, bool showParticles, int duration);  // showparticles and duration might be a in a different order

	__int64 eid;
	char event; // 0: None 1 : Add 2 : Modify 3 : Remove
	int effectId;
	int amplifier;
	bool showParticles;
	int duration;
};

class RemoveActorPacket : public Packet {
public:
	RemoveActorPacket();
};

class PlayerArmorDamagePacket : public Packet {
public:
	PlayerArmorDamagePacket();
};

class SetHealthPacket : public Packet {
public:
	SetHealthPacket();

	int health;
};