#pragma once

#ifndef PERFORMANCE_TEST
//#define PERFORMANCE_TEST
#endif

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <intrin.h>

#include <thread>
#include <unordered_map>

#include "../Horion/Command/CommandMgr.h"
#include "../Horion/Config/ConfigManager.h"
#include "../Horion/DrawUtils.h"
#include "../Horion/ImmediateGui.h"
#include "../Horion/Menu/ClickGui.h"
#include "../Horion/Module/ModuleManager.h"
#include "../SDK/BlockLegacy.h"
#include "../SDK/Camera.h"
#include "../SDK/ChestBlockActor.h"
#include "../SDK/GameMode.h"
#include "../SDK/MinecraftUIRenderContext.h"
#include "../SDK/MoveInputHandler.h"
#include "../SDK/RakNetConnector.h"
#include "../SDK/TextHolder.h"
#include "../SDK/UIScene.h"
#include "../Utils/Logger.h"
#include "../Utils/SkinUtil.h"
#include "../Utils/TextFormat.h"
#include "../resource.h"
#include "GameData.h"
#include "MinHook.h"

class VMTHook;
class FuncHook;

struct CoolSkinData {
	TextHolder unknown;
	TextHolder unknown2;
	TextHolder skinResourcePatch;  // 0x040
	TextHolder geometryName;       // 0x060 "geometry.humanoid.custom"
	unsigned char gap2[0x40];      // 0x080
	void* startAnimatedFrames;     // 0x0C0
	void* endAnimatedFrames;       // 0x0C8
	unsigned char gap3[0x8];       // 0x0D0
	TextHolder geometryData;       // 0x0D8
	TextHolder skinAnimationData;  // 0x0F8
	unsigned char gap4[0x20];      // 0x118
	bool isPremiumSkin;            // 0x138
	bool isPersonaSkin;
	bool isCapeOnClassicSkin;
	void* startPersonaPieces;
	void* endPersonaPieces;
	unsigned char gap5[0x8];  // 0x150
	TextHolder armSize;       // 0x158
	unsigned char gap6[0x8];  // 0x178
	void* startPieces;
};

class Hooks {
private:
	bool shouldRender = true;

public:
	char currentScreenName[100];
	std::vector<std::shared_ptr<FuncHook>> lambdaHooks;
	struct EntityListPointerHolder {
		Entity* ent;
		int addedTick;
	};
	std::vector<EntityListPointerHolder> entityList;
	__int64 RMBManager = 0;
	bool shouldLocalPlayerBeImmobile = false;

	static void Init();
	static void Restore();
	static void Enable();

private:
	static void Actor_baseTick(Entity* _this);
	static void* Player_tickWorld(Player* _this, __int64);
	static void ClientInstanceScreenModel_sendChatMessage(void* _this, TextHolder* text);
	static __int64 UIScene_render(UIScene* uiscene, __int64 screencontext);
	static __int64 RenderText(__int64 a1, MinecraftUIRenderContext* renderCtx);
	static float* Dimension_getFogColor(Dimension*, float* color, __int64 brightness, float a4);
	static float Dimension_getTimeOfDay(Dimension*, int a2, float a3);
	static float Dimension_getSunIntensity(Dimension*, float a2, Vec3* a3, float a4);
	static void ChestBlockActor_tick(ChestBlockActor*, BlockSource* source);
	static void Actor_lerpMotion(Entity* _this, Vec3);
	static int AppPlatform_getGameEdition(__int64 _this);
	static void PleaseAutoComplete(__int64 _this, __int64 a2, TextHolder* text, int a4);
	static void LoopbackPacketSender_sendToServer(LoopbackPacketSender* a, Packet* packet);
	static void LoopbackPacketSender_sendToClient(class networkhandler* _this, const void* networkIdentifier, Packet* packet, int a4);
	static void MultiLevelPlayer_tick(EntityList* entityList);
	static void GameMode_startDestroyBlock(GameMode* _this, Vec3i* a2, uint8_t face, void* a4, void* a5);
	static void HIDController_keyMouse(HIDController* _this, void* a2, void* a3);
	static int BlockLegacy_getRenderLayer(BlockLegacy* a1);
	static __int8* BlockLegacy_getLightEmission(BlockLegacy* _this, __int8* a2);
	static __int64 LevelRenderer_renderLevel(__int64 _this, __int64 a2, __int64 a3);
	static void ClickFunc(__int64 a1, char a2, char a3, __int16 a4, __int16 a5, __int16 a6, __int16 a7, char a8);
	static void MoveInputHandler_tick(__int64 a1, int* a2, uint32_t* a3, __int64* a4, MoveInputHandler* input, int a6);
	static __int64 ChestScreenController_tick(ChestScreenController* _this);
	static float GetGamma(uintptr_t* a1);
	static bool Actor_isInWater(Entity* _this);
	static void JumpPower(Entity* _this, float a2);
	static void Actor_ascendLadder(Entity* _this);
	static void Actor_swing(Entity* _this);
	static void Actor_startSwimming(Entity* _this);
	static float GameMode_getPickRange(GameMode* _this, __int64 a2, char a3);
	static __int64 GameMode_attack(GameMode* _this, Entity*);
	static __int64 ConnectionRequest_create(__int64 _this, __int64 privateKeyManager, void* a3, TextHolder* selfSignedId, TextHolder* serverAddress, __int64 clientRandomId, TextHolder* skinId, SkinData* skinData, __int64 capeData, __int64* serializedSkin, TextHolder* deviceId, int inputMode, int uiProfile, int guiScale, TextHolder* languageCode, bool sendEduModeParams, char a17, TextHolder* tenantId, __int64 a19, TextHolder* platformUserId, TextHolder* thirdPartyName, bool thirdPartyNameOnly, TextHolder* platformOnlineId, TextHolder* platformOfflineId, TextHolder* capeId, char a26);
	static void InventoryTransactionManager_addAction(InventoryTransactionManager* a1, InventoryAction* a2);
	static bool DirectoryPackAccessStrategy__isTrusted(__int64 _this);
	static bool ReturnTrue(__int64 _this);
	static __int64 SkinRepository___loadSkinPack(__int64 _this, __int64 pack, __int64 a3);
	static GamerTextHolder* toStyledString(__int64 strIn, GamerTextHolder* strOut);
	static __int64 MinecraftGame_onAppSuspended(__int64 _this);
	static __int64 InGamePlayScreen___renderLevel(__int64 playScreen, __int64 a2, __int64 a3);
	static void LocalPlayer__updateFromCamera(__int64 a1, Camera* camera, __int64* a3, Entity* a4);
	static bool Mob__isImmobile(Entity*);
	static void Actor__setRot(Entity* _this, Vec2& angle);
	static bool Actor_intersects(Entity* _this, Vec3 lower, Vec3 upper);
	static void InventoryTransactionManager__addAction(Player* _this, InventoryAction* a2, char a3);
	static void LevelRendererPlayer__renderNameTags(__int64 a1, __int64 a2, TextHolder* name, __int64 a4);
	static void KeyMapHookCallback(unsigned char key, bool isDown);
	static float getDestroySpeed(Player* _this, Block& block);
	static bool Actor_canSee(Entity* _this, Entity& entity);
	static bool Actor_shouldRender(Entity* _this);
	static bool Actor__isInWall(Entity* ent);

	//static void testFunction(class networkhandler* _this, const void* networkIdentifier, Packet* packet, int a4);

	std::unique_ptr<FuncHook> Actor_rotationHook;
	std::unique_ptr<FuncHook> setPosHook;
	std::unique_ptr<FuncHook> Actor_baseTickHook;
	std::unique_ptr<FuncHook> Player_tickWorldHook;
	std::unique_ptr<FuncHook> ClientInstanceScreenModel_sendChatMessageHook;
	std::unique_ptr<FuncHook> UIScene_renderHook;
	std::unique_ptr<FuncHook> RenderTextHook;
	std::unique_ptr<FuncHook> Dimension_getFogColorHook;
	std::unique_ptr<FuncHook> Dimension_getTimeOfDayHook;
	std::unique_ptr<FuncHook> Dimension_getSunIntensityHook;
	std::unique_ptr<FuncHook> ChestBlockActor_tickHook;
	std::unique_ptr<FuncHook> Actor_lerpMotionHook;
	std::unique_ptr<FuncHook> Actor_intersectsHook;
	std::unique_ptr<FuncHook> AppPlatform_getGameEditionHook;
	std::unique_ptr<FuncHook> PleaseAutoCompleteHook;
	std::unique_ptr<FuncHook> LoopbackPacketSender_sendToServerHook;
	std::unique_ptr<FuncHook> LoopbackPacketSender_sendToClientHook;
	std::unique_ptr<FuncHook> MultiLevelPlayer_tickHook;
	std::unique_ptr<FuncHook> GameMode_startDestroyBlockHook;
	std::unique_ptr<FuncHook> HIDController_keyMouseHook;
	std::unique_ptr<FuncHook> BlockLegacy_getRenderLayerHook;
	std::unique_ptr<FuncHook> BlockLegacy_getLightEmissionHook;
	std::unique_ptr<FuncHook> LevelRenderer_renderLevelHook;
	std::unique_ptr<FuncHook> ClickFuncHook;
	std::unique_ptr<FuncHook> MoveInputHandler_tickHook;
	std::unique_ptr<FuncHook> ChestScreenController_tickHook;
	std::unique_ptr<FuncHook> GetGammaHook;
	std::unique_ptr<FuncHook> Actor_isInWaterHook;
	std::unique_ptr<FuncHook> JumpPowerHook;
	std::unique_ptr<FuncHook> RMBManagerThingyHook;
	std::unique_ptr<FuncHook> MinecraftGame_onAppSuspendedHook;
	std::unique_ptr<FuncHook> Actor_ascendLadderHook;
	std::unique_ptr<FuncHook> Actor_swingHook;
	std::unique_ptr<FuncHook> Actor_lookAtHook;
	std::unique_ptr<FuncHook> Actor_startSwimmingHook;
	std::unique_ptr<FuncHook> GameMode_getPickRangeHook;
	std::unique_ptr<FuncHook> GameMode_attackHook;
	std::unique_ptr<FuncHook> ConnectionRequest_createHook;
	std::unique_ptr<FuncHook> InventoryTransactionManager_addActionHook;
	std::unique_ptr<FuncHook> DirectoryPackAccessStrategy__isTrustedHook;
	std::unique_ptr<FuncHook> ZipPackAccessStrategy__isTrustedHook;
	std::unique_ptr<FuncHook> SkinRepository___checkSignatureFileInPack;
	std::unique_ptr<FuncHook> SkinRepository___loadSkinPackHook;
	std::unique_ptr<FuncHook> toStyledStringHook;
	std::unique_ptr<FuncHook> swapchain__presentHook;
	std::unique_ptr<FuncHook> InGamePlayScreen___renderLevelHook;
	std::unique_ptr<FuncHook> swapchain__resizeBuffersHook;
	std::unique_ptr<FuncHook> LocalPlayer__updateFromCameraHook;
	std::unique_ptr<FuncHook> Mob__isImmobileHook;
	std::unique_ptr<FuncHook> Actor__setRotHook;
	std::unique_ptr<FuncHook> getDestroySpeedHook;
	std::unique_ptr<FuncHook> Actor__isInvisibleHook;
	std::unique_ptr<FuncHook> FishingHook___fishHookEventHook;
	std::unique_ptr<FuncHook> InventoryTransactionManager__addActionHook;
	std::unique_ptr<FuncHook> LevelRendererPlayer__renderNameTagsHook;
	std::unique_ptr<FuncHook> KeyMapHook;
	std::unique_ptr<FuncHook> testyHook;
	std::unique_ptr<FuncHook> Actor_canSeeHook;
	std::unique_ptr<FuncHook> Actor_shouldRenderHook;
	std::unique_ptr<FuncHook> ActorisInWallHook;
	//std::unique_ptr<FuncHook> testFunctionHook;
};

extern Hooks g_Hooks;

class FuncHook {
public:
	void* funcPtr;
	void* funcReal;

	FuncHook(void* func, void* hooked) {
		funcPtr = func;

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			logF("Invalid function pointer!");
			return;
		}

		MH_STATUS ret = MH_CreateHook(func, hooked, &funcReal);
		if (ret == MH_OK && (__int64)func > 10) {
			// Hook created successfully
		} else {
			logF("MH_CreateHook = %i", ret);
		}
	};

	FuncHook(uintptr_t func, void* hooked) {
		funcPtr = reinterpret_cast<void*>(func);

		// Check if the function pointer is valid
		if (IsBadReadPtr(funcPtr, sizeof(funcPtr))) {
			logF("Invalid function pointer!");
			return;
		}

		MH_STATUS ret = MH_CreateHook(funcPtr, hooked, &funcReal);
		if (ret == MH_OK && (__int64)funcPtr > 10) {
		} else {
			logF("MH_CreateHook = %i", ret);
		}
	};

	void enableHook(bool enable = true) {
		if (funcPtr != nullptr) {
			int ret = enable ? MH_EnableHook(funcPtr) : MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				logF("MH_EnableHook = %i", ret);
			}
		} else {
			logF("enableHook() called with nullptr func!");
		}
	}
	~FuncHook() {Restore();}
	// Restore the hook
	void Restore() {
		if (funcPtr != nullptr) {
			MH_STATUS ret = MH_DisableHook(funcPtr);
			if (ret != MH_OK) {
				logF("MH_DisableHook = %i", ret);
			}
		}
	}
	// Get the original function pointer with fastcall calling convention
	template <typename TRet, typename... TArgs>
	inline auto* GetFastcall() {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};
};