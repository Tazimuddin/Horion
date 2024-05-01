#include "Packet.h"

#include "../Utils/Utils.h"

TextHolder* Packet::getName() {
	return Utils::CallVFunc<2, TextHolder*>(this, new TextHolder());
}
LevelSoundEventPacket::LevelSoundEventPacket() {
	static uintptr_t** LevelSoundEventPacketVtable = 0x0;
	if (LevelSoundEventPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 89 51 30 F2");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		LevelSoundEventPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (LevelSoundEventPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(LevelSoundEventPacket));  // Avoid overwriting vtable
	vTable = LevelSoundEventPacketVtable;
	this->entityType.setText("minecraft:player");
}
PlayerAuthInputPacket::PlayerAuthInputPacket() {
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? ? ? C0 ? ? 00 C7 40 08 ? ? ? ? C7 40 0C ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 ? 48 89 4A ? 33 C9");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlayerAuthInputPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));  // Avoid overwriting vtable
	vTable = PlayerAuthInputPacketVtable;
}
PlayerAuthInputPacket::PlayerAuthInputPacket(Vec3 pos, float pitch, float yaw, float yawUnused) {
	static uintptr_t** PlayerAuthInputPacketVtable = 0x0;
	if (PlayerAuthInputPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? ? ? C0 ? ? 00 C7 40 08 ? ? ? ? C7 40 0C ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 ? 48 89 4A ? 33 C9");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		PlayerAuthInputPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (PlayerAuthInputPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerAuthInputPacket));  // Avoid overwriting vtable
	vTable = PlayerAuthInputPacketVtable;
	this->pos = pos;
	this->pitch = pitch;
	this->yaw = yaw;
	this->yawUnused = yawUnused;
	this->InputAD = 0.f;
	this->InputWS = 0.f;
}

MobEquipmentPacket::MobEquipmentPacket() {
	static uintptr_t** MobEquipmentPacketVtable = 0x0;
	if (MobEquipmentPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 06 48 8B C6 4C 8D 9C 24");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		MobEquipmentPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (MobEquipmentPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MobEquipmentPacket));  // Avoid overwriting vtable
	vTable = MobEquipmentPacketVtable;
}

MobEquipmentPacket::MobEquipmentPacket(__int64 entityRuntimeId, ItemStack& item, int hotbarSlot, int inventorySlot) {
	memset(this, 0x0, sizeof(MobEquipmentPacket));
	using MobEquimentPacketConstructor_t = void(__fastcall*)(MobEquipmentPacket*, __int64, ItemStack&, int, int, char);
	static MobEquimentPacketConstructor_t MobEquimentPacketConstructor = reinterpret_cast<MobEquimentPacketConstructor_t>(FindSignature("48 8D 05 ? ? ? ? 48 89 06 48 8B C6 4C 8D 9C 24"));

	if (MobEquimentPacketConstructor != 0)
		MobEquimentPacketConstructor(this, entityRuntimeId, item, hotbarSlot, inventorySlot, 0);
}

InventoryTransactionPacket::InventoryTransactionPacket() {
	static uintptr_t** InventoryTransactionPacketVtable = 0x0;
	if (InventoryTransactionPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? 48 89 4D ? 48 8D 35");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		InventoryTransactionPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (InventoryTransactionPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(InventoryTransactionPacket));  // Avoid overwriting vtable
	vTable = InventoryTransactionPacketVtable;
}
TextPacket::TextPacket() {
	static uintptr_t** textPacketVtable = 0x0;
	if (textPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 44 24 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 48 8B 4D");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		textPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (textPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(TextPacket));  // Avoid overwriting vtable
	vTable = textPacketVtable;

	messageType = 1;  // TYPE_CHAT
}
MovePlayerPacket::MovePlayerPacket() {
	static uintptr_t** movePlayerPacketVtable = 0x0;
	if (movePlayerPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 42 ? 48 8B 47");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		movePlayerPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (movePlayerPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MovePlayerPacket));  // Avoid overwriting vtable
	vTable = movePlayerPacketVtable;
}
MovePlayerPacket::MovePlayerPacket(LocalPlayer* player, Vec3 pos) {
	static uintptr_t** movePlayerPacketVtable = 0x0;
	if (movePlayerPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 42 ? 48 8B 47");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		movePlayerPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (movePlayerPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MovePlayerPacket));  // Avoid overwriting vtable
	vTable = movePlayerPacketVtable;
	entityRuntimeID = player->getRuntimeIDComponent()->runtimeID;
	Position = pos;
	pitch = player->getActorHeadRotationComponent()->rot.x;
	yaw = player->getActorRotationComponent()->rot.y;
	headYaw = player->getActorHeadRotationComponent()->rot.y;
	onGround = true;
	mode = 0;
}
PlayerActionPacket::PlayerActionPacket() {
	static uintptr_t** playerActionPacketVtable = 0x0;
	if (playerActionPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? 48 89 4C ? ? ? ? C0 66");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerActionPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerActionPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerActionPacket));  // Avoid overwriting vtable
	vTable = playerActionPacketVtable;
}

SubChunkRequestPacket::SubChunkRequestPacket() {
	static uintptr_t** subChunkRequestPacketVtable = 0x0;
	if (subChunkRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? 48 89 4C ? ? ? ? C0 66");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		subChunkRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (subChunkRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SubChunkRequestPacket));  // Avoid overwriting vtable
	vTable = subChunkRequestPacketVtable;
}

EmotePacket::EmotePacket() {
	static uintptr_t** emotePacketVtable = 0x0;
	if (emotePacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 85 ? ? ? ? 48 89 8D ? ? ? ? 4C 89 AD");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		emotePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (emotePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(EmotePacket));  // Avoid overwriting vtable
	vTable = emotePacketVtable;
}

AnimatePacket::AnimatePacket() {
	static uintptr_t** animatePacketVtable = 0x0;
	if (animatePacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 44 ? ? 48 8B 43 ? 48 8B 08");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		animatePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (animatePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(AnimatePacket));  // Avoid overwriting vtable
	vTable = animatePacketVtable;
}

AnimatePacket::AnimatePacket(int action, __int64 entityRuntimeID, float rowingTime) {
	static uintptr_t** animatePacketVtable = 0x0;
	if (animatePacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 44 ? ? 48 8B 43 ? 48 8B 08");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		animatePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (animatePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(AnimatePacket));  // Avoid overwriting vtable
	vTable = animatePacketVtable;
	this->action = action;
	this->entityId = entityRuntimeID;
	this->rowingTime = rowingTime;
}

NPCRequestPacket::NPCRequestPacket() {
	static uintptr_t** npcRequestPacketVtable = 0x0;
	if (npcRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 03 48 89 53 30");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		npcRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (npcRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(NPCRequestPacket));  // Avoid overwriting vtable
	vTable = npcRequestPacketVtable;
}

PlayerSkinPacket::PlayerSkinPacket() {
	static uintptr_t** playerSkinPacketVtable = 0x0;
	if (playerSkinPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 89 79 30 48 89 79 38 48 83 C1 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerSkinPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerSkinPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerSkinPacket));  // Avoid overwriting vtable
	vTable = playerSkinPacketVtable;
}

NetworkLatencyPacket::NetworkLatencyPacket() {
	static uintptr_t** networkLatencyPacketVtable = 0x0;
	if (networkLatencyPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 44 24 ? 49 8B 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		networkLatencyPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (networkLatencyPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(NetworkLatencyPacket));  // Avoid overwriting vtable
	vTable = networkLatencyPacketVtable;
}

CommandRequestPacket::CommandRequestPacket() {
	static uintptr_t** commandRequestPacketVtable = 0x0;
	if (commandRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? ? ? 00 C7 40 08 ? ? ? ? C7 40 0C ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 ? 48 89 42 ? 89 42 38 48 89 42 ? 48 89 42 ? 88 42 60 C7 42 18");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		commandRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (commandRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));  // Avoid overwriting vtable
	vTable = commandRequestPacketVtable;
}

CommandRequestPacket::CommandRequestPacket(std::string cmd) {
	static uintptr_t** commandRequestPacketVtable = 0x0;
	if (commandRequestPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? ? ? 00 C7 40 08 ? ? ? ? C7 40 0C ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 ? 48 89 42 ? 89 42 38 48 89 42 ? 48 89 42 ? 88 42 60 C7 42 18");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		commandRequestPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (commandRequestPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(CommandRequestPacket));  // Avoid overwriting vtable
	vTable = commandRequestPacketVtable;
	this->origin = Origin::PLAYER;
	this->isExternal = 0;
}

InteractPacket::InteractPacket(/*enum InteractPacket::Action, class ActorRuntimeID, Vec3 const&*/) {
	static uintptr_t** interactPacketVtable = 0x0;
	if (interactPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 88 48 40 48 89 48 48 48 89 48 50");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		interactPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (interactPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(InteractPacket));  // Avoid overwriting vtable
	vTable = interactPacketVtable;
}

BookEditPacket::BookEditPacket() {
	static uintptr_t** bookEditPacketVtable = 0x0;
	if (bookEditPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 44 ? ? C7 44 24 ? ? ? ? ? 4C 89 7C ? ? 4C 89 7D ? 48 C7 45 ? ? ? ? ? 44 88 7C ? ? 4C 89 7D ? 4C 89 7D ? 48 C7 45 ? ? ? ? ? 44 88 7D ? 4C 89 7D ? 4C 89 7D ? 48 C7 45 ? ? ? ? ? 44 88 7D ? 41 8B 46 ? 44 88 7C");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		bookEditPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
#ifdef _DEBUG
		if (bookEditPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(BookEditPacket));
	vTable = bookEditPacketVtable;
}

DisconnectPacket::DisconnectPacket() {
	static uintptr_t** disconnectPacketVtable = 0x0;
	if (disconnectPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 45 ? 40 88 75 ? 48 89 75 ? 48 89 75 ? 48 C7 45");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		disconnectPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
#ifdef _DEBUG
		if (disconnectPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(DisconnectPacket));
	vTable = disconnectPacketVtable;
}

DisconnectPacket::DisconnectPacket(TextHolder reason, bool hideDisconnectScreen) {
	static uintptr_t** disconnectPacketVtable = 0x0;
	if (disconnectPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 45 ? 40 88 75 ? 48 89 75 ? 48 89 75 ? 48 C7 45");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		disconnectPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
#ifdef _DEBUG
		if (disconnectPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(DisconnectPacket));
	vTable = disconnectPacketVtable;
	this->hideDisconnectScreen = hideDisconnectScreen;
	this->reason = reason;
}

ResourcePacksInfoPacket::ResourcePacksInfoPacket() {
	static uintptr_t** resourcePacksInfoPacketVtable = 0x0;
	if (resourcePacksInfoPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? ? ? 00 C7 40 08 ? ? ? ? C7 40 0C ? ? ? ? 48 8D 05 ? ? ? ? 48 89 02 33 C0 48 89 42 ? 48 89 42 ? 89 42 38 89 42 40 48 89 42 ? 48 89 42 ? 48 89 42 ? 48 89 42 ? 48 89 42");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		resourcePacksInfoPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
#ifdef _DEBUG
		if (resourcePacksInfoPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ResourcePacksInfoPacket));  // Avoid overwriting vtable
	vTable = resourcePacksInfoPacketVtable;
}

SetPlayerGameTypePacket::SetPlayerGameTypePacket() {
	static uintptr_t** setPlayerGameTypePacketVtable = 0x0;
	if (setPlayerGameTypePacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 44 ? ? 89 7C 24 ? 48 8B 8B ? ? ? ? 48 8B 01 48 8D 54 ? ? 48 8B 40 ? FF 15 ? ? ? ? 90 8B D7");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		setPlayerGameTypePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (setPlayerGameTypePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SetPlayerGameTypePacket));  // Avoid overwriting vtable
	vTable = setPlayerGameTypePacketVtable;
}

ActorEventPacket::ActorEventPacket() {
	static uintptr_t** actorEvenPacketVtable = 0x0;
	if (actorEvenPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 48 89 48 40 88 48 48 89 48 4C");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		actorEvenPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (actorEvenPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ActorEventPacket));  // Avoid overwriting vtable
	vTable = actorEvenPacketVtable;
}

ActorEventPacket::ActorEventPacket(uint64_t entityRuntimeId, char eventId, int16_t itemId) {
	static uintptr_t** actorEventPacketVtable = 0x0;
	if (actorEventPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 48 89 48 40 88 48 48 89 48 4C");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		actorEventPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (actorEventPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(ActorEventPacket));  // Avoid overwriting vtable
	vTable = actorEventPacketVtable;
	this->entityRuntimeId = entityRuntimeId;
	this->eventId = eventId;
	this->itemId = itemId;
}

PlayerHotbarPacket::PlayerHotbarPacket() { //Client
	static uintptr_t** playerHotbarPacketVtable = 0x0;
	if (playerHotbarPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 89 48 40 C7 40 ? ? ? ? ? C7 40 ? ? ? ? ? 66 C7 40 ? ? ? 48 89 50 10 66 C7 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerHotbarPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerHotbarPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerHotbarPacket));  // Avoid overwriting vtable
	vTable = playerHotbarPacketVtable;
}

PlayerHotbarPacket::PlayerHotbarPacket(int selectedHotbarSlot, char containerId, bool selectHotbarSlot) { //Client
	static uintptr_t** playerHotbarPacketVtable = 0x0;
	if (playerHotbarPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 89 48 40 C7 40 ? ? ? ? ? C7 40 ? ? ? ? ? 66 C7 40 ? ? ? 48 89 50 10 66 C7 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerHotbarPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerHotbarPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerHotbarPacket));  // Avoid overwriting vtable
	vTable = playerHotbarPacketVtable;
	this->selectedHotbarSlot = selectedHotbarSlot;
	this->containerId = containerId;
	this->selectHotbarSlot = selectHotbarSlot;
}

MobEffectPacket::MobEffectPacket() { //Client
	static uintptr_t** mobEffectPacketVtable = 0x0;
	if (mobEffectPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 48 89 48 40 89 48 48 88 48 4C 48 89 48 50 88 48 58");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		mobEffectPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (mobEffectPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MobEffectPacket));  // Avoid overwriting vtable
	vTable = mobEffectPacketVtable;
}

MobEffectPacket::MobEffectPacket(__int64 entityRuntimeId, char event, int effectId, int amplifier, bool showParticles, int duration) { //Client
	static uintptr_t** mobEffectPacketVtable = 0x0;
	if (mobEffectPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 15 ? ? ? ? C7 40 ? ? ? ? ? 33 C9 C7 40 ? ? ? ? ? 48 89 48 28 48 89 48 30 89 48 38 48 89 48 40 89 48 48 88 48 4C 48 89 48 50 88 48 58");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		mobEffectPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (mobEffectPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(MobEffectPacket));  // Avoid overwriting vtable
	vTable = mobEffectPacketVtable;
	this->eid = entityRuntimeId;
	this->event = event;
	this->effectId = effectId;
	this->amplifier = amplifier;
	this->duration = duration;
	this->showParticles = showParticles;
}

RemoveActorPacket::RemoveActorPacket() { //Client
	static uintptr_t** removeActorPacketVtable = 0x0;
	if (removeActorPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? 48 89 48 ? C7 40 18 ? ? ? ? C7 40 1C ? ? ? ? 66 C7 40 ? ? ? 48 C7 40 ? ? ? ? ? EB");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		removeActorPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (removeActorPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(RemoveActorPacket));  // Avoid overwriting vtable
	vTable = removeActorPacketVtable;
}

PlayerArmorDamagePacket::PlayerArmorDamagePacket() { //Client
	static uintptr_t** playerArmorDamagePacketVtable = 0x0;
	if (playerArmorDamagePacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 0D ? ? ? ? 48 89 48 ? 33 C9 C7 40");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		playerArmorDamagePacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (playerArmorDamagePacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(PlayerArmorDamagePacket));  // Avoid overwriting vtable
	vTable = playerArmorDamagePacketVtable;
}

SetHealthPacket::SetHealthPacket() {  // Client
	static uintptr_t** setHealthPacketVtable = 0x0;
	if (setHealthPacketVtable == 0x0) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 8B C1 C7 41 0C ? ? ? ? 66 C7 41 ? ? ? 89 51 30 C3");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		setHealthPacketVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
#ifdef _DEBUG
		if (setHealthPacketVtable == 0x0 || sigOffset == 0x0)
			__debugbreak();
#endif
	}
	memset(this, 0, sizeof(SetHealthPacket));  // Avoid overwriting vtable
	vTable = setHealthPacketVtable;
}
