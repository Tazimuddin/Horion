#include "Hooks.h"

#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_transform.hpp>  // perspective, translate, rotate
#include <glm/gtc/constants.hpp>
#include <glm/mat4x4.hpp>         // mat4
#include <glm/trigonometric.hpp>  // radians

#include "../Horion/Loader.h"
#include "../Horion/Menu/TabGui.h"
#include "../SDK/Tag.h"
#include "../Utils/ClientColors.h"
#include "../Utils/ColorUtil.h"

Hooks g_Hooks;
bool isTicked = false;
bool overrideStyledReturn = false;
TextHolder styledReturnText;
//#define TEST_DEBUG

void Hooks::Init() {
	logF("Setting up Hooks...");
	// clang-format off

	// Signatures
	{
		// vtables better than sigs

		void* _renderCtx = reinterpret_cast<void*>(FindSignature("48 8B ? 48 89 ? ? 55 56 57 41 ? 41 ? 41 ? 41 ? 48 8D ? ? ? ? ? 48 81 EC ? ? ? ? 0F 29 ? ? 0F 29 ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? 4C 8B ? 48 89 ? ? ? 4C 8B"));
		g_Hooks.RenderTextHook = std::make_unique<FuncHook>(_renderCtx, Hooks::RenderText);
		g_Hooks.RenderTextHook->enableHook();

		void* render = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 48 89 74 ? ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 ? ? ? ? ? 48 8B FA 48 8B D9 B9"));
		g_Hooks.UIScene_renderHook = std::make_unique<FuncHook>(render, Hooks::UIScene_render);

		void* key = reinterpret_cast<void*>(FindSignature("48 83 EC ? 0F B6 C1 4C 8D 05"));
		g_Hooks.KeyMapHook = std::make_unique<FuncHook>(key, Hooks::KeyMapHookCallback);

		void* _sendChatMessage = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 89 54 24 ? 48 8B D9 48 8B 49"));
		g_Hooks.ClientInstanceScreenModel_sendChatMessageHook = std::make_unique<FuncHook>(_sendChatMessage, Hooks::ClientInstanceScreenModel_sendChatMessage);

		void* fogColorFunc = reinterpret_cast<void*>(FindSignature("41 0F 10 08 48 8B C2 0F"));
		g_Hooks.Dimension_getFogColorHook = std::make_unique<FuncHook>(fogColorFunc, Hooks::Dimension_getFogColor);
		
		void* timeOfDay = reinterpret_cast<void*>(FindSignature("44 8B C2 B8 ? ? ? ? F7 EA"));
		g_Hooks.Dimension_getTimeOfDayHook = std::make_unique<FuncHook>(timeOfDay, Hooks::Dimension_getTimeOfDay);

		void* sunItensity = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B B9 ? ? ? ? 49 8B D8"));
		g_Hooks.Dimension_getSunIntensityHook = std::make_unique<FuncHook>(sunItensity, Hooks::Dimension_getSunIntensity);

		void* chestTick = reinterpret_cast<void*>(FindSignature("40 53 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 ? ? 48 83 79"));
		g_Hooks.ChestBlockActor_tickHook = std::make_unique<FuncHook>(chestTick, Hooks::ChestBlockActor_tick);

		void* getRenderLayer = reinterpret_cast<void*>(FindSignature("8B 81 E4 ? ? ? C3 CC CC CC CC CC CC CC CC CC F3"));
		g_Hooks.BlockLegacy_getRenderLayerHook = std::make_unique<FuncHook>(getRenderLayer, Hooks::BlockLegacy_getRenderLayer);

		void* getLightEmission = reinterpret_cast<void*>(FindSignature("0F B6 81 ? ? ? ? 88 02 48 8B C2 C3 CC CC CC 0F B6 81"));
		g_Hooks.BlockLegacy_getLightEmissionHook = std::make_unique<FuncHook>(getLightEmission, Hooks::BlockLegacy_getLightEmission);

		void* getGameEdition = reinterpret_cast<void*>(FindSignature("8B 91 ?? ?? ?? ?? 85 D2 74 1C 83 EA 01"));
		g_Hooks.AppPlatform_getGameEditionHook = std::make_unique<FuncHook>(getGameEdition, Hooks::AppPlatform_getGameEdition);

		void* tick_entityList = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 57 48 83 EC ? 48 8B D9 FF 15 ? ? ? ? 48 8B F8 FF 15 ? ? ? ? 48 81 FF ? ? ? ? 75 ? 48 6B C0 ? EB ? 48 99 48 F7 FF 48 8B C8 48 69 C2 ? ? ? ? 48 69 C9 ? ? ? ? 48 99 48 F7 FF 48 03 C1 48 2B 83 ? ? ? ? 48 B9 ? ? ? ? ? ? ? ? 48 3B C1 7C"));
		g_Hooks.MultiLevelPlayer_tickHook = std::make_unique<FuncHook>(tick_entityList, Hooks::MultiLevelPlayer_tick);

		void* keyMouseFunc = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC ? ? ? ? ? ? 74 24 ? ? ? 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F8"));
		g_Hooks.HIDController_keyMouseHook = std::make_unique<FuncHook>(keyMouseFunc, Hooks::HIDController_keyMouse);

		void* renderLevel = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 55 56 57 48 8D AC ? ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F8 48 8B DA 48 8B F1 ? ? C0"));
		g_Hooks.LevelRenderer_renderLevelHook = std::make_unique<FuncHook>(renderLevel, Hooks::LevelRenderer_renderLevel);

		void* Actor_intersectsAddr = reinterpret_cast<void*>(FindSignature("48 83 EC ? 48 8B 81 ? ? ? ? 48 85 C0 74 50"));
		g_Hooks.Actor_intersectsHook = std::make_unique<FuncHook>(Actor_intersectsAddr, Hooks::Actor_intersects);

		void* clickHook = reinterpret_cast<void*>(FindSignature("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 44 0F B7 BC 24 ? ? ? ? 48 8B D9"));
		g_Hooks.ClickFuncHook = std::make_unique<FuncHook>(clickHook, Hooks::ClickFunc);

		void* chestScreenControllerTick = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 48 89 6C ? ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 0F 29 74 ? ? 0F 29 7C"));
		g_Hooks.ChestScreenController_tickHook = std::make_unique<FuncHook>(chestScreenControllerTick, Hooks::ChestScreenController_tick);

		void* autoComplete = reinterpret_cast<void*>(FindSignature("48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 8B D9"));
		g_Hooks.PleaseAutoCompleteHook = std::make_unique<FuncHook>(autoComplete, Hooks::PleaseAutoComplete);

		void* fullbright = reinterpret_cast<void*>(FindSignature("48 83 EC ? 80 B9 ? ? ? ? ? 48 8D 54 ? ? 48 8B 01 48 8B 40 ? 74 38 41 B8 16 ? ? ?"));
		g_Hooks.GetGammaHook = std::make_unique<FuncHook>(fullbright, Hooks::GetGamma);

		void* ConnectionRequest__create = reinterpret_cast<void*>(FindSignature("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC ? ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B D9 48 89 55"));
		g_Hooks.ConnectionRequest_createHook = std::make_unique<FuncHook>(ConnectionRequest__create, Hooks::ConnectionRequest_create);

		void* _getSkinPack = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC ? ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 8B F1 33 DB"));
		g_Hooks.SkinRepository___loadSkinPackHook = std::make_unique<FuncHook>(_getSkinPack, Hooks::SkinRepository___loadSkinPack);

#ifdef TEST_DEBUG
		void* addAction = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 55 56 57 41 56 41 57 48 83 EC ? 45 0F B6 ? 4C 8B F2 48 8B F9"));
		g_Hooks.InventoryTransactionManager__addActionHook = std::make_unique<FuncHook>(addAction, Hooks::InventoryTransactionManager__addAction);
#endif

		void* localPlayerUpdateFromCam = reinterpret_cast<void*>(FindSignature("48 8B C4 48 89 70 ? 57 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78"));
		g_Hooks.LocalPlayer__updateFromCameraHook = std::make_unique<FuncHook>(localPlayerUpdateFromCam, Hooks::LocalPlayer__updateFromCamera);

		void* renderNameTags = reinterpret_cast<void*>(FindSignature("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F1"));
		g_Hooks.LevelRendererPlayer__renderNameTagsHook = std::make_unique<FuncHook>(renderNameTags, Hooks::LevelRendererPlayer__renderNameTags);
		
		void* destroySpeed = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 57 48 83 EC ? 48 8B FA ? ? 74 24 ? 48 8B 91"));
		g_Hooks.getDestroySpeedHook = std::make_unique<FuncHook>(destroySpeed, Hooks::getDestroySpeed);

		void* Actor_canSee = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 ? ? ? ? ? 48 8B F1 48 8B DA"));
		g_Hooks.Actor_canSeeHook = std::make_unique<FuncHook>(Actor_canSee, Hooks::Actor_canSee);

		void* Actor_shouldRender = reinterpret_cast<void*>(FindSignature("48 83 EC ? 48 8B 01 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 0F 94 C0 48 83 C4 ? C3 CC CC 48 89 5C"));
		g_Hooks.Actor_shouldRenderHook = std::make_unique<FuncHook>(Actor_shouldRender, Hooks::Actor_shouldRender);

		void* actorisInWall = reinterpret_cast<void*>(FindSignature("40 53 48 83 EC 50 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B 01 48 8D 54 24"));
		g_Hooks.ActorisInWallHook = std::make_unique<FuncHook>(actorisInWall, Hooks::Actor__isInWall);

		void* MoveInputHandler_tickAddr = reinterpret_cast<void*>(FindSignature("48 89 5C ? ? 55 56 57 41 56 41 57 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B 01"));
		g_Hooks.MoveInputHandler_tickHook = std::make_unique<FuncHook>(MoveInputHandler_tickAddr, Hooks::MoveInputHandler_tick);
		
		static constexpr auto counterStart = __COUNTER__ + 1;
		#define lambda_counter (__COUNTER__ - counterStart)

		void* levelRendererBobView = reinterpret_cast<void*>(FindSignature("48 8B C4 48 89 58 20 57 48 ?? ?? ?? ?? 00 00 0F ?? ?? ?? 0F ?? ?? ?? ?? 0F ?? ?? ?? ?? 0F ?? ?? ??"));

		static auto bobViewHookF = [](__int64 _this, glm::mat4& matrix, float lerpT){
			static auto origFunc = g_Hooks.lambdaHooks.at(lambda_counter)->GetFastcall<void, __int64, glm::mat4&, float>();
			
			static auto testMod = moduleMgr->getModule<ViewModel>();
			auto p = Game.getLocalPlayer();
			float degrees = fmodf(p->getPosOld()->lerp(p->getPos(), lerpT).x, 5) - 2.5f;
			degrees *= 180 / 2.5f;

			auto pos = Game.getClientInstance()->levelRenderer->getOrigin();
			
			glm::mat4 View = matrix;
			
			matrix = View;
			if (testMod->isEnabled()) {
				if (testMod->doTranslate)
					matrix = glm::translate<float>(matrix, glm::vec3(testMod->xTrans, testMod->yTrans, testMod->zTrans));

				if (testMod->doScale)
					matrix = glm::scale<float>(matrix, glm::vec3(testMod->xMod, testMod->yMod, testMod->zMod));
			}
			return origFunc(_this, matrix, lerpT);
		};
		
		using BobViewHookFunc = decltype(&bobViewHookF.operator());
		auto bobViewHook = std::make_shared<FuncHook>(levelRendererBobView, static_cast<BobViewHookFunc>(bobViewHookF));

		g_Hooks.lambdaHooks.push_back(bobViewHook);

		#undef lambda_counter

		logF("Hooks initialized");
	}

	// Vtables
	{
		// LoopbackPacketSender::vtable
		if (Game.getClientInstance()->loopbackPacketSender != nullptr) {
			uintptr_t** packetSenderVtable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)Game.getClientInstance()->loopbackPacketSender);
			if (packetSenderVtable == nullptr)
				logF("LoopbackPacketSenderVtable is invalid");
			else {
				g_Hooks.LoopbackPacketSender_sendToServerHook = std::make_unique<FuncHook>(packetSenderVtable[2], Hooks::LoopbackPacketSender_sendToServer);

				g_Hooks.LoopbackPacketSender_sendToClientHook = std::make_unique<FuncHook>(packetSenderVtable[4], Hooks::LoopbackPacketSender_sendToClient); //I use the second sendToClient
			}
		} else logF("LoopbackPacketSender is null");

		// LocalPlayer::vtable
		{
			uintptr_t** localPlayerVtable = GetVtableFromSig("48 8D 05 ? ? ? ? 48 89 01 B8 ? ? ? ? 8D 50 FA 44 8D 48 ? 44 8D 40 ? 66 89 44 ? ? E8 ? ? ? ? 48 8B 8B", 3);
			if (localPlayerVtable == 0x0)
				logF("LocalPlayer signature not working!!!");
			else {
				g_Hooks.Actor_startSwimmingHook = std::make_unique<FuncHook>(localPlayerVtable[195], Hooks::Actor_startSwimming);

				g_Hooks.Actor_ascendLadderHook = std::make_unique<FuncHook>(localPlayerVtable[331], Hooks::Actor_ascendLadder);
				
				//g_Hooks.Actor__setRotHook = std::make_unique<FuncHook>(localPlayerVtable[27], Hooks::Actor__setRot); // Removed :(

				g_Hooks.Actor_swingHook = std::make_unique<FuncHook>(localPlayerVtable[213], Hooks::Actor_swing);

				//g_Hooks.JumpPowerHook = std::make_unique<FuncHook>(localPlayerVtable[352], Hooks::JumpPower); //jump from ground with movement proxy

				//g_Hooks.setPosHook = std::make_unique<FuncHook>(localPlayerVtable[19], Hooks::setPos);

				g_Hooks.Actor_lerpMotionHook = std::make_unique<FuncHook>(localPlayerVtable[46], Hooks::Actor_lerpMotion);

				g_Hooks.Actor_baseTickHook = std::make_unique<FuncHook>(localPlayerVtable[49], Hooks::Actor_baseTick);

				g_Hooks.Mob__isImmobileHook = std::make_unique<FuncHook>(localPlayerVtable[90], Hooks::Mob__isImmobile);

				g_Hooks.Actor_isInWaterHook = std::make_unique<FuncHook>(localPlayerVtable[70], Hooks::Actor_isInWater);

				g_Hooks.Player_tickWorldHook = std::make_unique<FuncHook>(localPlayerVtable[352], Hooks::Player_tickWorld);

				//g_Hooks.Actor__isInvisibleHook = std::make_unique<FuncHook>(localPlayerVtable[59], Hooks::Actor__isInvisible);
			}
		}

		// GameMode::vtable
		{
			uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 48 89 01 48 89 51 ? 48 C7 41 ? ? ? ? ? C7 41");
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			uintptr_t** gameModeVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + /*length of instruction*/ 7);
			if (gameModeVtable == 0x0 || sigOffset == 0x0)
				logF("GameMode signature not working!!!");
			else {
				g_Hooks.GameMode_startDestroyBlockHook = std::make_unique<FuncHook>(gameModeVtable[1], Hooks::GameMode_startDestroyBlock);

				g_Hooks.GameMode_getPickRangeHook = std::make_unique<FuncHook>(gameModeVtable[10], Hooks::GameMode_getPickRange);

				g_Hooks.GameMode_attackHook = std::make_unique<FuncHook>(gameModeVtable[14], Hooks::GameMode_attack);
			}
		}

		// PackAccessStrategy vtables for isTrusted
		{
			uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 49 89 06 49 8D 76 ? 45 33 E4");
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			uintptr_t** directoryPackVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
			//uintptr_t** directoryPackVtable = GetVtableFromSig("48 8D 05 ? ? ? ? 49 89 06 49 8D 76 ? 45 33 E4", 3);
			if (directoryPackVtable == 0x0)
				logF("directoryPackVtable signature not working!!!");
			else g_Hooks.DirectoryPackAccessStrategy__isTrustedHook = std::make_unique<FuncHook>(directoryPackVtable[6], Hooks::DirectoryPackAccessStrategy__isTrusted);

			uintptr_t sigOffset2 = FindSignature("48 8D 05 ? ? ? ? 48 89 03 48 83 3E ? ? ? ? ? ? ? 45 33 E4");
			int offset2 = *reinterpret_cast<int*>(sigOffset2 + 3);
			uintptr_t** directoryPackVtable2 = reinterpret_cast<uintptr_t**>(sigOffset2 + offset2 + 7);
			//uintptr_t** directoryPackVtable2 = GetVtableFromSig("48 8D 05 ? ? ? ? 48 89 03 48 83 3E ? 0F 84 ? ? ? ? 33 ED", 3);
			if (directoryPackVtable2 == 0x0)
				logF("directoryPackVtable2 signature not working!!!");
			else g_Hooks.ZipPackAccessStrategy__isTrustedHook = std::make_unique<FuncHook>(directoryPackVtable2[6], Hooks::ReturnTrue);
			
			g_Hooks.SkinRepository___checkSignatureFileInPack = std::make_unique<FuncHook>(FindSignature("48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B 79"), Hooks::ReturnTrue);
		}
		logF("Vtables initialized");
	}

	// clang-format on
}

void Hooks::Restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	Sleep(10);
}

void Hooks::Enable() {
	logF("Hooks enabled");
	MH_EnableHook(MH_ALL_HOOKS);
}

bool Hooks::Actor_intersects(Entity* _this, Vec3 lower, Vec3 upper) {
	static auto oTick = g_Hooks.Actor_intersectsHook->GetFastcall<bool, Entity*, Vec3, Vec3>();

	if (moduleMgr != nullptr && _this != nullptr && Game.getLocalPlayer() != nullptr && _this == Game.getLocalPlayer())
		moduleMgr->onPlayerTick(reinterpret_cast<Player*>(_this));

	if (!Game.getLocalPlayer() || !Game.getLocalPlayer()->level || !Game.getLocalPlayer()->getRegion() || !Game.isInGame())
		g_Hooks.entityList.clear();

	if (Game.getLocalPlayer() != nullptr && _this == Game.getLocalPlayer()) {
		std::vector<EntityListPointerHolder> validEntities;
		for (const auto& ent : g_Hooks.entityList) {
			auto entity = ent.ent;
			MEMORY_BASIC_INFORMATION info;
			VirtualQuery(ent.ent, &info, sizeof(MEMORY_BASIC_INFORMATION));
			if (info.State & MEM_FREE) continue;
			if (info.State & MEM_RESERVE) continue;

			if (entity == nullptr) continue;

			if (entity != nullptr && (__int64)entity != 0xFFFFFFFFFFFFFCD7 && ent.ent != nullptr && *(__int64*)ent.ent != 0xFFFFFFFFFFFFFCD7 &&
				*(__int64*)ent.ent > 0x6FF000000000 && *(__int64*)ent.ent < 0x800000000000 && *((int64_t*)ent.ent + 1) < 0x6FF000000000 &&
				*(__int64*)ent.ent <= (__int64)(Utils::getBase() + 0x10000000) && entity->isAlive()) {
				validEntities.push_back(ent);
			}
		}
		g_Hooks.entityList.clear();
		g_Hooks.entityList = validEntities;
	}
	return oTick(_this, lower, upper);
}

void* Hooks::Player_tickWorld(Player* _this, __int64 unk) {
	static auto oTick = g_Hooks.Player_tickWorldHook->GetFastcall<void*, Player*, __int64>();
	auto o = oTick(_this, unk);

	if (_this != nullptr && Game.getLocalPlayer() != nullptr && _this == Game.getLocalPlayer()) {
		GameMode* gm = Game.getLocalPlayer()->getGameMode();
		if (_this && gm) {
			GameData::updateGameData(gm);
			moduleMgr->onWorldTick(gm);
		}
	}
	return o;
}

void Hooks::ClientInstanceScreenModel_sendChatMessage(void* _this, TextHolder* text) {
	static auto oSendMessage = g_Hooks.ClientInstanceScreenModel_sendChatMessageHook->GetFastcall<void, void*, TextHolder*>();

	if (text->getTextLength() <= 0)
		return oSendMessage(_this, text);

	auto message = text->getText();
	if (*message == cmdMgr->prefix) {
		cmdMgr->execute(message);
		return;
	} else if (*message == '.') {
		static std::once_flag flag;
		std::call_once(flag, [] {
			Game.getClientInstance()->getGuiData()->displayClientMessageF("%sYour Horion prefix is: \"%s%c%s\"", RED, YELLOW, cmdMgr->prefix, RED);
			Game.getClientInstance()->getGuiData()->displayClientMessageF("%sEnter \"%s%cprefix .%s\" to reset your prefix", RED, YELLOW, cmdMgr->prefix, RED);
		});
	}
	return oSendMessage(_this, text);
}

void Hooks::Actor_baseTick(Entity* ent) {
	static auto oFunc = g_Hooks.Actor_baseTickHook->GetFastcall<void, Entity*>();
	LocalPlayer* player = Game.getLocalPlayer();
	if (!player || !player->getLevel()) return oFunc(ent);

	static int tickCountThen = 0;
	int tickCountNow = *(int*)((__int64)player->getLevel() + 0x690);

	if (tickCountNow != tickCountThen) {
		g_Hooks.entityList.clear();
		tickCountThen = tickCountNow;
	}

	moduleMgr->onBaseTick(ent);

	if (ent->isClientSide()) {
		EntityListPointerHolder e;
		e.addedTick = tickCountNow;
		e.ent = ent;

		bool found = false;
		for (const auto& entity : g_Hooks.entityList)
			if (entity.ent == ent && entity.addedTick == tickCountNow) {
				found = true;
				break;
			}

		if (!found)
			g_Hooks.entityList.push_back(e);
	}
	return oFunc(ent);
}

void Hooks::KeyMapHookCallback(unsigned char key, bool isDown) {
	static auto oFunc = g_Hooks.KeyMapHook->GetFastcall<void, unsigned char, bool>();
	bool shouldCancel = false;
	GameData::keys[key] = isDown;

	moduleMgr->onKey((int)key, isDown, shouldCancel);
	moduleMgr->onKeyUpdate((int)key, (isDown && GameData::canUseMoveKeys()));
	TabGui::onKeyUpdate((int)key, isDown);
	ClickGui::onKeyUpdate((int)key, isDown);

	if (shouldCancel) return;
	return oFunc(key, isDown);
}

__int64 Hooks::UIScene_render(UIScene* uiscene, __int64 screencontext) {
	static auto oRender = g_Hooks.UIScene_renderHook->GetFastcall<__int64, UIScene*, __int64>();
	static auto hudModule = moduleMgr->getModule<HudModule>();

	g_Hooks.shouldRender = false;

	TextHolder alloc{};
	uiscene->getScreenName(&alloc);

	if (!g_Hooks.shouldRender) {
		g_Hooks.shouldRender = (strcmp(alloc.getText(), "debug_screen") == 0);
		if (!g_Hooks.shouldRender)
			if (alloc.getTextLength() < 100) strcpy_s(g_Hooks.currentScreenName, alloc.getText());
	}

	alloc.alignedTextLength = 0;

	if (!g_Hooks.shouldRender) {
		if (hudModule && !hudModule->alwaysShow)
			g_Hooks.shouldRender = (!strcmp(g_Hooks.currentScreenName, "hud_screen") || !strcmp(g_Hooks.currentScreenName, "start_screen"));
	}

	return oRender(uiscene, screencontext);
}

__int64 Hooks::RenderText(__int64 a1, MinecraftUIRenderContext* renderCtx) {
	static auto oText = g_Hooks.RenderTextHook->GetFastcall<__int64, __int64, MinecraftUIRenderContext*>();

	GuiData* dat = Game.getClientInstance()->getGuiData();

	DrawUtils::setCtx(renderCtx, dat);
	{
		if (GameData::shouldHide() || !moduleMgr->isInitialized() || !g_Hooks.shouldRender)
			return oText(a1, renderCtx);

		static auto hudModule = moduleMgr->getModule<HudModule>();
		static auto clickGuiModule = moduleMgr->getModule<ClickGuiMod>();
		static auto clientThemeModule = moduleMgr->getModule<ClientTheme>();


		Game.frameCount++;

		auto wid = Game.getClientInstance()->getGuiData()->windowSize;

		// Call PreRender() functions
		moduleMgr->onPreRender(renderCtx);
		clientThemeModule->onRender(renderCtx);
		DrawUtils::flush();

		__int64 retval = oText(a1, renderCtx);

		bool shouldPostRender = true;
		bool shouldRenderArrayList = true;
		bool shouldRenderTabGui = true;
		bool shouldRenderWatermark = true;
		static float rcolors[4];          // Rainbow color array RGBA
		static float disabledRcolors[4];  // Rainbow Colors, but for disabled modules
		static float currColor[4];        // ArrayList colors
		static float SurgeColor[4];       // ArrayList colors

		// Rainbow color updates
		{
			Utils::ApplyRainbow(rcolors);  // Increase Hue of rainbow color array
			disabledRcolors[0] = std::min(1.f, rcolors[0] * 0.4f + 0.2f);
			disabledRcolors[1] = std::min(1.f, rcolors[1] * 0.4f + 0.2f);
			disabledRcolors[2] = std::min(1.f, rcolors[2] * 0.4f + 0.2f);
			disabledRcolors[3] = 1;
		}
		Utils::ApplyRainbow(currColor, 0.00025f);
		if (currColor[0] += 1.f) {
			currColor[0] += 1.f;
		}
		Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], currColor[0], currColor[1], currColor[2]);
		Utils::ColorConvertHSVtoRGB(currColor[0], currColor[1], currColor[2], currColor[0], currColor[3], currColor[3]);
		{
			{
				// Main Menu
				std::string screenName(g_Hooks.currentScreenName);
				if (strcmp(screenName.c_str(), "start_screen") == 0) {
					// Main Menu
					std::string screenName(g_Hooks.currentScreenName);
					Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

					if (screenName == "start_screen") {
						Vec2 text(1.0f, 5.0f);
						Vec2 outline(1.0f, 5.5f);

						MC_Color Color(255, 255, 0);
						std::string string;
						string = "Horion";
						DrawUtils::drawText(text, &string, Color, 2.0f, 1.0f);

						text.y += 18.0f;
						string = "Version: 1.20.0.1";
						DrawUtils::drawText(text, &string, Color, 1.0f, 1.0f);
						text.y += 15.0f;
						string =
							"Credits: \n"
							"\n"
							"\n";
						DrawUtils::drawText(text, &string, Color, 1.0f, 1.0f);
					}
				} else {
					if (clickGuiModule->isEnabled()) {
						ClickGui::render();
						shouldPostRender = false;
					}
				}
			}
			// Main Menu
			std::string screenName(g_Hooks.currentScreenName);
			Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
			float CycleSpeed = 5.0f;
			float Saturation = 5.0f;
			int separation = 0;
			int index = 0;
			if (strcmp(screenName.c_str(), "start_screen") == 0) {
				if (strcmp(screenName.c_str(), "start_screen") == 0) {
				}
				// Draw BIG epic horion watermark
				{
				}
			} else {
				shouldRenderTabGui = hudModule->tabgui && hudModule->isEnabled();
				shouldRenderArrayList = hudModule->arraylist && hudModule->isEnabled();
				shouldRenderWatermark = hudModule->watermark && hudModule->isEnabled();

				if (clickGuiModule->isEnabled()) {
					ClickGui::render();
					shouldPostRender = false;
					shouldRenderArrayList = false;
					shouldRenderTabGui = false;
					shouldRenderWatermark = false;
				}

				if (shouldRenderTabGui) TabGui::render();

				{
					Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

					if (shouldRenderWatermark) {
						constexpr float nameTextSize = 1.5f;
						constexpr float versionTextSize = 0.7f;
						static const float textHeight = (nameTextSize + versionTextSize * 0.7f /* We don't quite want the version string in its own line, just a bit below the name */) * DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight();
						constexpr float borderPadding = 1;
						constexpr float margin = 5;

						static std::string name = "Horion";
#ifdef _DEBUG
						static std::string version = "dev";
#elif defined _BETA
						static std::string version = "beta";
#else
						static std::string version = "public";
#endif

						float nameLength = DrawUtils::getTextWidth(&name, nameTextSize);
						float fullTextLength = nameLength + DrawUtils::getTextWidth(&version, versionTextSize);
						Vec4 rect = Vec4(
							windowSize.x - margin - fullTextLength - borderPadding * 2,
							windowSize.y - margin - textHeight,
							windowSize.x - margin + borderPadding,
							windowSize.y - margin);

						DrawUtils::drawRectangle(rect, MC_Color(), 1.f, 2.f);
						DrawUtils::fillRectangle(rect, ClientColors::watermarkBackgroundColor, 1.f);
						DrawUtils::drawText(Vec2(rect.x + borderPadding, rect.y), &name, MC_Color(), nameTextSize);
						DrawUtils::drawText(Vec2(rect.x + borderPadding + nameLength, rect.w - 7), &version, MC_Color(), versionTextSize);
					}
				}
			}
		}

		if (shouldPostRender) moduleMgr->onPostRender(renderCtx);
		DrawUtils::flush();
		std::shared_ptr<InfoBoxData> firstBox = Game.getFreshInfoBox();
		std::vector<std::shared_ptr<InfoBoxData>>& allBoxes = Game.getInfoBoxList();
		if (!allBoxes.empty()) {
			float yOffset = wid.y;  // Starting y-position at the bottom of the screen

			for (auto& box : allBoxes) {
				box->fade();
				if (box->fadeTarget == 1 && box->closeTimer <= 0 && box->closeTimer > -1)
					box->fadeTarget = 0;
				else if (box->closeTimer > 0 && box->fadeVal > 0.9f)
					box->closeTimer -= 1.f / 60;

				const float paddingHoriz = 20;  // Adjusted horizontal padding
				const float paddingVert = 5;    // Adjusted vertical padding
				const float titleTextSize = box->fadeVal * 2;
				const float messageTextSize = box->fadeVal * 1;
				const float titleTextHeight = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * titleTextSize;

				int lines = 1;
				std::string substring = box->message;
				while (lines < 5) {
					auto brea = substring.find("\n");
					if (brea == std::string::npos || brea + 1 >= substring.size())
						break;
					substring = substring.substr(brea + 1);
					lines++;
				}
				if (box->message.size() == 0)
					lines = 0;

				const float messageHeight = DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() * messageTextSize * lines;

				float titleWidth = DrawUtils::getTextWidth(&box->title, titleTextSize);
				float msgWidth = DrawUtils::getTextWidth(&box->message, messageTextSize);
				Vec2 bottomRight(wid.x - paddingHoriz - std::max(titleWidth, msgWidth) / 2, yOffset - paddingVert * 2 - titleTextHeight - messageHeight * lines - paddingVert);
				Vec2 textPos = Vec2(bottomRight.x - titleWidth / 2, bottomRight.y);
				Vec2 msgPos = Vec2(bottomRight.x - msgWidth / 2, textPos.y + titleTextHeight + paddingVert);
				Vec4 rectPos = Vec4(
					bottomRight.x - paddingHoriz - std::max(titleWidth, msgWidth) / 2,
					bottomRight.y - paddingVert,
					bottomRight.x + paddingHoriz + std::max(titleWidth, msgWidth) / 2,
					bottomRight.y + paddingVert * 2 + titleTextHeight + messageHeight * lines);
				DrawUtils::fillRectangle(rectPos, MC_Color(12, 12, 12), box->fadeVal);
				DrawUtils::drawRectangle(rectPos, currColor, box->fadeVal, 2.f);
				DrawUtils::drawText(textPos, &box->title, MC_Color(), titleTextSize, box->fadeVal);
				DrawUtils::drawText(msgPos, &box->message, MC_Color(), messageTextSize, box->fadeVal);

				// Animate the box's upward movement when it opens
				if (box->isOpen) {
					if (box->fadeVal > 0.001f) yOffset -= paddingVert * 2 + titleTextHeight + messageHeight * lines + paddingVert;
				}
			}
		}
		DrawUtils::shouldToggleLeftClick = false;
		DrawUtils::shouldToggleRightClick = false;
		DrawUtils::flush();
		return retval;
	}
}

float* Hooks::Dimension_getFogColor(Dimension* _this, float* color, __int64 a3, float a4) {
	static auto oGetFogColor = g_Hooks.Dimension_getFogColorHook->GetFastcall<float*, Dimension*, float*, __int64, float>();
	MC_Color rColor = ColorUtil::getRainbowColor(3, 0.5f, 1, 1);
	static auto nightMod = moduleMgr->getModule<NightMode>();
	if (nightMod->isEnabled()) {
		color[0] = 0.f;
		color[1] = 0.f;
		color[2] = 0.2f;
		color[3] = 1;
		return color;
	}

	static auto rainbowSkyMod = moduleMgr->getModule<RainbowSky>();
	if (rainbowSkyMod->isEnabled()) {
		color[0] = rColor.r;
		color[1] = rColor.g;
		color[2] = rColor.b;
		color[3] = 1;
		return color;
	}
	return oGetFogColor(_this, color, a3, a4);
}

float Hooks::Dimension_getTimeOfDay(Dimension* _this, int time, float a) {
	static auto oGetTimeOfDay = g_Hooks.Dimension_getTimeOfDayHook->GetFastcall<float, Dimension*, int, float>();

	static auto timeChange = moduleMgr->getModule<TimeChanger>();
	if (timeChange->isEnabled()) {
		return timeChange->modifier;
	}

	return oGetTimeOfDay(_this, time, a);
}

float Hooks::Dimension_getSunIntensity(Dimension* _this, float a, Vec3* viewVector, float minInfluenceAngle) {
	static auto oGetSunIntensity = g_Hooks.Dimension_getSunIntensityHook->GetFastcall<float, Dimension*, float, Vec3*, float>();

	static auto nightMod = moduleMgr->getModule<NightMode>();
	if (nightMod->isEnabled()) {
		return -0.5f;
	}

	return oGetSunIntensity(_this, a, viewVector, minInfluenceAngle);
}

void Hooks::ChestBlockActor_tick(ChestBlockActor* _this, BlockSource* source) {
	static auto oTick = g_Hooks.ChestBlockActor_tickHook->GetFastcall<void, ChestBlockActor*, BlockSource*>();
	oTick(_this, source);
	static auto* storageEspMod = moduleMgr->getModule<StorageESP>();
	if (_this != nullptr && storageEspMod->isEnabled())
		GameData::addChestToList(_this);
}

void Hooks::Actor_lerpMotion(Entity* _this, Vec3 motVec) {
	static auto oLerp = g_Hooks.Actor_lerpMotionHook->GetFastcall<void, Entity*, Vec3>();

	if (Game.getLocalPlayer() != _this)
		return oLerp(_this, motVec);

	static auto noKnockbackmod = moduleMgr->getModule<Velocity>();
	if (noKnockbackmod->isEnabled()) {
		static void* networkSender = nullptr;
		if (!networkSender)
			networkSender = reinterpret_cast<void*>(16 + FindSignature("48 8B CB 48 8B 80 ? ? ? ? FF 15 ? ? ? ? C6 46 ? ? 48 8B 5C 24"));

		if (networkSender == _ReturnAddress()) {
			motVec = _this->entityLocation->velocity.lerp(motVec, noKnockbackmod->xModifier, noKnockbackmod->yModifier, noKnockbackmod->xModifier);
		}
	}

	oLerp(_this, motVec);
}

int Hooks::AppPlatform_getGameEdition(__int64 _this) {
	static auto oGetEditon = g_Hooks.AppPlatform_getGameEditionHook->GetFastcall<signed int, __int64>();

	static auto mod = moduleMgr->getModule<EditionFaker>();
	if (mod->isEnabled()) {
		return mod->getFakedEditon();
	}

	return oGetEditon(_this);
}

void Hooks::PleaseAutoComplete(__int64 a1, __int64 a2, TextHolder* text, int a4) {
	static auto oAutoComplete = g_Hooks.PleaseAutoCompleteHook->GetFastcall<void, __int64, __int64, TextHolder*, int>();
	char* tx = text->getText();
	if (tx != nullptr && text->getTextLength() >= 1 && tx[0] == '.') {
		std::string search = tx + 1;                                              // Dont include the '.'
		std::transform(search.begin(), search.end(), search.begin(), ::tolower);  // make the search text lowercase

		struct LilPlump {
			std::string cmdAlias;
			IMCCommand* command = 0;
			bool shouldReplace = true;  // Should replace the current text in the box (autocomplete)

			bool operator<(const LilPlump& o) const {
				return cmdAlias < o.cmdAlias;
			}
		};  // This is needed so the std::set sorts it alphabetically

		std::set<LilPlump> searchResults;

		std::vector<IMCCommand*>* commandList = cmdMgr->getCommandList();
		for (auto it = commandList->begin(); it != commandList->end(); ++it) {  // Loop through commands
			IMCCommand* c = *it;
			auto* aliasList = c->getAliasList();
			for (auto it = aliasList->begin(); it != aliasList->end(); ++it) {  // Loop through aliases
				std::string cmd = *it;
				LilPlump plump;

				for (size_t i = 0; i < search.size(); i++) {  // Loop through search string
					char car = search.at(i);
					if (car == ' ' && i == cmd.size()) {
						plump.shouldReplace = false;
						break;
					} else if (i >= cmd.size())
						goto outerContinue;

					if (car != cmd.at(i))  // and compare
						goto outerContinue;
				}
				// Not at outerContinue? Then we got a good result!
				{
					cmd.insert(0, 1, '.');  // Prepend the '.'

					plump.cmdAlias = cmd;
					plump.command = c;
					searchResults.emplace(plump);
				}

			outerContinue:
				continue;
			}
		}

		if (!searchResults.empty()) {
			LilPlump firstResult = *searchResults.begin();

			size_t maxReplaceLength = firstResult.cmdAlias.size();
			if (searchResults.size() > 1) {
				for (auto it = searchResults.begin()++; it != searchResults.end(); it++) {
					auto alias = it->cmdAlias;
					maxReplaceLength = std::min(maxReplaceLength, alias.size());

					for (int i = 0; i < maxReplaceLength; i++) {
						if (alias[i] != firstResult.cmdAlias[i]) {
							maxReplaceLength = i;
							break;
						}
					}
				}
			} else
				maxReplaceLength = firstResult.cmdAlias.size();

			Game.getGuiData()->displayClientMessageF("==========");
			if (searchResults.size() > 1) {
				for (auto it = searchResults.begin(); it != searchResults.end(); ++it) {
					LilPlump plump = *it;
					Game.getGuiData()->displayClientMessageF("%s%s - %s%s", plump.cmdAlias.c_str(), GRAY, ITALIC, plump.command->getDescription());
				}
			}
			if (firstResult.command->getUsage(firstResult.cmdAlias.c_str() + 1)[0] == 0)
				Game.getGuiData()->displayClientMessageF("%s%s %s- %s", WHITE, firstResult.cmdAlias.c_str(), GRAY, firstResult.command->getDescription());
			else
				Game.getGuiData()->displayClientMessageF("%s%s %s %s- %s", WHITE, firstResult.cmdAlias.c_str(), firstResult.command->getUsage(firstResult.cmdAlias.c_str() + 1 /*exclude prefix*/), GRAY, firstResult.command->getDescription());

			if (firstResult.shouldReplace) {
				if (search.size() == firstResult.cmdAlias.size() - 1 && searchResults.size() == 1) {
					maxReplaceLength++;
					firstResult.cmdAlias.append(" ");
				}
				text->setText(firstResult.cmdAlias.substr(0, maxReplaceLength));  // Set text
				using syncShit = void(__fastcall*)(TextHolder*, TextHolder*);
				static syncShit sync = reinterpret_cast<syncShit>(FindSignature("40 53 48 83 EC ? 48 8B DA 48 8D 4C 24 ? E8 ? ? ? ? 90 48 8B 40 ? 48 8B 08 48 8B 01 48 8B D3 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 33 C0 48 89 44 24 ? 48 8B 4C 24 ? 48 89 44 24 ? 48 85 C9 74 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? E8 ? ? ? ? 80 7C 24 ? ? 74 ? 48 8B 4C 24 ? E8 ? ? ? ? 48 83 C4"));
				sync(text, text);
			}
		}
		return;
	}
	oAutoComplete(a1, a2, text, a4);
}

void Hooks::LoopbackPacketSender_sendToServer(LoopbackPacketSender* a, Packet* packet) {
	static auto oFunc = g_Hooks.LoopbackPacketSender_sendToServerHook->GetFastcall<void, LoopbackPacketSender*, Packet*>();

	static auto autoSneakMod = moduleMgr->getModule<AutoSneak>();
	static auto blinkMod = moduleMgr->getModule<Blink>();
	static auto noPacketMod = moduleMgr->getModule<NoPacket>();
	static auto noSwingMod = moduleMgr->getModule<NoSwing>();

	if (noSwingMod->isEnabled() && noSwingMod->server && packet->isInstanceOf<AnimatePacket>())
		return;

	if (noPacketMod->isEnabled() && Game.isInGame())
		return;

	if (blinkMod->isEnabled()) {
		if (packet->isInstanceOf<MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>()) {
			if (blinkMod->isEnabled()) {
				if (packet->isInstanceOf<MovePlayerPacket>()) {
					MovePlayerPacket* meme = reinterpret_cast<MovePlayerPacket*>(packet);
					meme->onGround = true;                                                            // Don't take Fall Damages when turned off
					blinkMod->getMovePlayerPacketHolder()->push_back(new MovePlayerPacket(*meme));  // Saving the packets
				} else {
					blinkMod->getPlayerAuthInputPacketHolder()->push_back(new PlayerAuthInputPacket(*reinterpret_cast<PlayerAuthInputPacket*>(packet)));
				}
			}
			return;  // Dont call LoopbackPacketSender_sendToServer
		}
	} else if (!blinkMod->isEnabled()) {
		if (blinkMod->getMovePlayerPacketHolder()->size() > 0) {
			for (auto it : *blinkMod->getMovePlayerPacketHolder()) {
				oFunc(a, (it));
				delete it;
				it = nullptr;
			}
			blinkMod->getMovePlayerPacketHolder()->clear();
			return;
		}
		if (blinkMod->getPlayerAuthInputPacketHolder()->size() > 0) {
			for (auto it : *blinkMod->getPlayerAuthInputPacketHolder()) {
				oFunc(a, (it));
				delete it;
				it = nullptr;
			}
			blinkMod->getPlayerAuthInputPacketHolder()->clear();
			return;
		}
	}

	if (autoSneakMod->isEnabled() && Game.getLocalPlayer() != nullptr && autoSneakMod->doSilent && packet->isInstanceOf<PlayerActionPacket>()) {
		auto* pp = reinterpret_cast<PlayerActionPacket*>(packet);

		if (pp->action == 12 && pp->entityRuntimeId == Game.getLocalPlayer()->getRuntimeIDComponent()->runtimeID)
			return;  // dont send uncrouch
	}

	moduleMgr->onSendPacket(packet);

	/*if (strcmp(packet->getName()->getText(), "EmotePacket") == 0) {
		auto varInt = reinterpret_cast<__int64*>(reinterpret_cast<__int64>(packet) + 0x28);
		auto text = reinterpret_cast<TextHolder*>(reinterpret_cast<__int64>(packet) + 0x30);
		auto bet = reinterpret_cast<unsigned char*>(reinterpret_cast<__int64>(packet) + 0x50);
		logF("emote %llX %s %i", *varInt, text->getText(), *bet);
	} fix emote crashing*/

	oFunc(a, packet);
}

void Hooks::LoopbackPacketSender_sendToClient(networkhandler* _this, const void* networkIdentifier, Packet* packet, int subId) {
	static auto func = g_Hooks.LoopbackPacketSender_sendToClientHook->GetFastcall<void, networkhandler*, const void*, Packet*, int>();

	moduleMgr->onSendClientPacket(packet);
	func(_this, networkIdentifier, packet, subId);
}

void Hooks::MultiLevelPlayer_tick(EntityList* _this) {
	static auto oTick = g_Hooks.MultiLevelPlayer_tickHook->GetFastcall<void, EntityList*>();
	GameMode* gm = Game.getGameMode();
	if (gm != nullptr) moduleMgr->onTick(gm);
	oTick(_this);
	GameData::EntityList_tick(_this);
}

void Hooks::GameMode_startDestroyBlock(GameMode* _this, Vec3i* a2, uint8_t face, void* a4, void* a5) {
	static auto oFunc = g_Hooks.GameMode_startDestroyBlockHook->GetFastcall<void, GameMode*, Vec3i*, uint8_t, void*, void*>();

	static auto nukerModule = moduleMgr->getModule<Nuker>();

	if (nukerModule->isEnabled()) {
		Vec3i tempPos;

		int range = nukerModule->getNukerRadius();
		const bool isVeinMiner = nukerModule->isVeinMiner();
		const bool isAutoMode = nukerModule->isAutoMode();

		BlockSource* region = Game.getLocalPlayer()->region;
		auto selectedBlockId = ((region->getBlock(*a2)->blockLegacy))->blockId;
		uint8_t selectedBlockData = region->getBlock(*a2)->data;

		if (!isAutoMode) {
			for (int x = -range; x < range; x++) {
				for (int y = -range; y < range; y++) {
					for (int z = -range; z < range; z++) {
						tempPos.x = a2->x + x;
						tempPos.y = a2->y + y;
						tempPos.z = a2->z + z;
						if (tempPos.y > 0) {
							Block* blok = region->getBlock(tempPos);
							uint8_t data = blok->data;
							auto id = blok->blockLegacy->blockId;
							if (blok->blockLegacy->material->isSolid == true && (!isVeinMiner || (id == selectedBlockId && data == selectedBlockData)))
								_this->destroyBlock(&tempPos, face);
						}
					}
				}
			}
		}
		return;
	}

	oFunc(_this, a2, face, a4, a5);
}

void Hooks::HIDController_keyMouse(HIDController* _this, void* a2, void* a3) {
	static auto oFunc = g_Hooks.HIDController_keyMouseHook->GetFastcall<void, HIDController*, void*, void*>();
	GameData::setHIDController(_this);
	isTicked = true;
	oFunc(_this, a2, a3);
	return;
}

int Hooks::BlockLegacy_getRenderLayer(BlockLegacy* a1) {
	static auto oFunc = g_Hooks.BlockLegacy_getRenderLayerHook->GetFastcall<int, BlockLegacy*>();

	static auto xrayMod = moduleMgr->getModule<Xray>();
	if (xrayMod->isEnabled()) {
		char* text = a1->name.getText();
		if (strstr(text, "ore") == NULL)
			if (strcmp(text, "lava") != NULL)
				if (strcmp(text, "water") != NULL)
					if (strcmp(text, "portal") != NULL)
						if (strcmp(text, "amethyst_block") != NULL)
							if (strcmp(text, "ancient_debris") != NULL)
								if (strcmp(text, "command_block") != NULL)
									if (strcmp(text, "repeating_command_block") != NULL)
										if (strcmp(text, "chain_command_block") != NULL)
											if (strcmp(text, "structure_block") != NULL)
												if (strcmp(text, "deny") != NULL)
													if (strcmp(text, "allow") != NULL)
														if (strcmp(text, "bedrock") != NULL)
															if (strcmp(text, "border_block") != NULL)
																return 10;
	}
	return oFunc(a1);
}

__int8* Hooks::BlockLegacy_getLightEmission(BlockLegacy* a1, __int8* a2) {
	static auto oFunc = g_Hooks.BlockLegacy_getLightEmissionHook->GetFastcall<__int8*, BlockLegacy*, __int8*>();
	static auto xrayMod = moduleMgr->getModule<Xray>();

	if (!xrayMod || !xrayMod->isEnabled())
		return oFunc(a1, a2);

	*a2 = 15;
	return a2;
}

__int64 Hooks::LevelRenderer_renderLevel(__int64 _this, __int64 a2, __int64 a3) {
	static auto oFunc = g_Hooks.LevelRenderer_renderLevelHook->GetFastcall<__int64, __int64, __int64, __int64>();

	using reloadShit_t = void(__fastcall*)(__int64, unsigned __int64*, char);
	static reloadShit_t reloadChunk = nullptr;

	if (!reloadChunk) {
		// RenderChunkCoordinator::rebuildAllRenderChunkGeometry
		reloadChunk = reinterpret_cast<reloadShit_t>(FindSignature("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 45 0F B6 F0"));
	}

	static auto xrayMod = moduleMgr->getModule<Xray>();

	static bool lastState = false;
	if (lastState != xrayMod->isEnabled()) {
		// LevelRenderer::rebuildAllRenderChunkGeometry
		lastState = xrayMod->isEnabled();
		unsigned long long* v5;  // rdi
		unsigned long long* i;   // rbx

		v5 = *(unsigned long long**)(_this + 32);
		for (i = (unsigned long long*)*v5; i != v5; i = (unsigned long long*)*i)
			reloadChunk(i[3], v5, 1);
	}

	auto ret = oFunc(_this, a2, a3);

	DrawUtils::setGameRenderContext(a2);
	moduleMgr->onLevelRender();
	DrawUtils::setGameRenderContext(0);

	return ret;
}

void Hooks::ClickFunc(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
	static auto oFunc = g_Hooks.ClickFuncHook->GetFastcall<void, __int64, char, char, __int16, __int16, __int16, __int16, char>();
	static auto clickGuiModule = moduleMgr->getModule<ClickGuiMod>();

	// MouseButtons
	// 0 = mouse move
	// 1 = left click
	// 2 = right click
	// 3 = middle click
	// 4 = scroll   (isDown: 120 (SCROLL UP) and -120 (SCROLL DOWN))

	DrawUtils::onMouseClickUpdate((int)mouseButton, isDown);

	if (isDown)
		if (mouseButton == 1)
			Game.leftclickCount++;
		else if (mouseButton == 2)
			Game.rightclickCount++;

	if (clickGuiModule->isEnabled()) {
		if (mouseButton == 4) {
			ClickGui::onWheelScroll(isDown > 0);
		}
		if (mouseButton != 0)  // Mouse click event
			return;
	}
	return oFunc(a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8);
}

void Hooks::MoveInputHandler_tick(__int64 a1, int* a2, uint32_t* a3, __int64* a4, MoveInputHandler* input, int a6) {
	static auto oTick = g_Hooks.MoveInputHandler_tickHook->GetFastcall<__int64, __int64, int*, uint32_t*, __int64*, MoveInputHandler*, int>();

	oTick(a1, a2, a3, a4, input, a6);
	moduleMgr->onMove(input);
}

__int64 Hooks::ChestScreenController_tick(ChestScreenController* a1) {
	static auto oFunc = g_Hooks.ChestScreenController_tickHook->GetFastcall<__int64, ChestScreenController*>();

	static auto chestStealerMod = moduleMgr->getModule<ChestStealer>();
	if (chestStealerMod->isEnabled()) chestStealerMod->chestScreenController_tick(a1);

	return oFunc(a1);
}

float Hooks::GetGamma(uintptr_t* a1) {
	static auto fullbright = moduleMgr->getModule<FullBright>();
	static auto xrayMod = moduleMgr->getModule<Xray>();
	static auto nametagmod = moduleMgr->getModule<NameTags>();
	static auto viewMod = moduleMgr->getModule<ViewModel>();

	uintptr_t** list = (uintptr_t**)a1;

	char obtainedSettings = 0;
	bool hadIt = false;
	for (uint16_t i = 3; i < 450; i++) {
		if (list[i] == nullptr) continue;
		uintptr_t* info = *(uintptr_t**)((uintptr_t)list[i] + 8);
		if (info == nullptr) continue;

		TextHolder* translateName = (TextHolder*)((uintptr_t)info + 0x108);
		TextHolder* settingname = (TextHolder*)((uintptr_t)info + 0x158);

		if (!strcmp(translateName->getText(), "options.smoothlighting")) {
			if (hadIt) continue;
			bool* smoothlightning = (bool*)((uintptr_t)list[i] + 16);
			xrayMod->smoothLightningSetting = smoothlightning;
			obtainedSettings++;
			hadIt = true;
		} else if (!strcmp(settingname->getText(), "gfx_ingame_player_names")) {
			bool* ingamePlayerName = (bool*)((uintptr_t)list[i] + 16);
			nametagmod->ingameNametagSetting = ingamePlayerName;
			obtainedSettings++;
		} else if (!strcmp(settingname->getText(), "gfx_viewbobbing")) {
			bool* viewbobbing = (bool*)((uintptr_t)list[i] + 16);
			if (viewMod->isEnabled())
				*viewbobbing = true;
			obtainedSettings++;
		}
		if (obtainedSettings == 3) break;
	}

	if (xrayMod->isEnabled())
		return 25.f;

	if (fullbright->isEnabled())
		return fullbright->intensity;

	static auto ofunc = g_Hooks.GetGammaHook->GetFastcall<float, uintptr_t*>();
	return ofunc(a1);
}

bool Hooks::Actor_isInWater(Entity* _this) {
	static auto oFunc = g_Hooks.Actor_isInWaterHook->GetFastcall<bool, Entity*>();
	static auto airSwimModule = moduleMgr->getModule<AirSwim>();

	if (Game.getLocalPlayer() != _this)
		return oFunc(_this);
	else if (airSwimModule && airSwimModule->isEnabled())
		return true;
	else
		return oFunc(_this);
}

void Hooks::JumpPower(Entity* a1, float a2) {
	static auto oFunc = g_Hooks.JumpPowerHook->GetFastcall<void, Entity*, float>();
	static auto highJumpMod = moduleMgr->getModule<HighJump>();
	if (highJumpMod->isEnabled() && Game.getLocalPlayer() == a1) {
		a1->entityLocation->velocity.y = highJumpMod->jumpPower;
		return;
	}
	oFunc(a1, a2);
}

void Hooks::Actor_ascendLadder(Entity* _this) {
	static auto oFunc = g_Hooks.Actor_ascendLadderHook->GetFastcall<void, Entity*>();

	static auto fastLadderModule = moduleMgr->getModule<FastLadder>();
	if (fastLadderModule->isEnabled() && Game.getLocalPlayer() == _this) {
		_this->entityLocation->velocity.y = fastLadderModule->speed;
		return;
	}
	return oFunc(_this);
}

void Hooks::Actor_swing(Entity* _this) {
	static auto oFunc = g_Hooks.Actor_swingHook->GetFastcall<void, Entity*>();
	static auto noSwingMod = moduleMgr->getModule<NoSwing>();
	if (noSwingMod->isEnabled() && !noSwingMod->server)
		return;

	oFunc(_this);
}

void Hooks::Actor_startSwimming(Entity* _this) {
	static auto oFunc = g_Hooks.Actor_startSwimmingHook->GetFastcall<void, Entity*>();

	static auto jesusModule = moduleMgr->getModule<Jesus>();
	if (jesusModule->isEnabled() && Game.getLocalPlayer() == _this)
		return;

	oFunc(_this);
}

float Hooks::GameMode_getPickRange(GameMode* _this, __int64 currentInputMode, char isVR) {
	static auto oFunc = g_Hooks.GameMode_getPickRangeHook->GetFastcall<float, GameMode*, __int64, char>();

	if (Game.getLocalPlayer() != nullptr) {
		static auto BlockReachModule = moduleMgr->getModule<BlockReach>();
		if (BlockReachModule->isEnabled())
			return BlockReachModule->getBlockReach();

		static auto teleportModule = moduleMgr->getModule<Teleport>();
		if (teleportModule->isEnabled())
			return 255;
	}

	return oFunc(_this, currentInputMode, isVR);
}

__int64 Hooks::ConnectionRequest_create(__int64 _this, __int64 privateKeyManager, void* a3, TextHolder* selfSignedId, TextHolder* serverAddress, __int64 clientRandomId, TextHolder* skinId, SkinData* skinData, __int64 capeData, __int64* serializedSkin, TextHolder* deviceId, int inputMode, int uiProfile, int guiScale, TextHolder* languageCode, bool sendEduModeParams, char a17, TextHolder* tenantId, __int64 a19, TextHolder* platformUserId, TextHolder* thirdPartyName, bool thirdPartyNameOnly, TextHolder* platformOnlineId, TextHolder* platformOfflineId, TextHolder* capeId, char a26) {
	static auto oFunc = g_Hooks.ConnectionRequest_createHook->GetFastcall<__int64, __int64, __int64, void*, TextHolder*, TextHolder*, __int64, TextHolder*, SkinData*, __int64, __int64*, TextHolder*, int, int, int, TextHolder*, bool, char, TextHolder*, __int64, TextHolder*, TextHolder*, bool, TextHolder*, TextHolder*, TextHolder*, char>();

	return oFunc(_this, privateKeyManager, a3, selfSignedId, serverAddress, clientRandomId, skinId, skinData, capeData, serializedSkin, deviceId, inputMode, uiProfile, guiScale, languageCode, sendEduModeParams, a17, tenantId, a19, platformUserId, thirdPartyName, thirdPartyNameOnly, platformOnlineId, platformOfflineId, capeId, a26);
}

void Hooks::InventoryTransactionManager_addAction(InventoryTransactionManager* _this, InventoryAction* action) {
	static auto Func = g_Hooks.InventoryTransactionManager_addActionHook->GetFastcall<void, InventoryTransactionManager*, InventoryAction*>();
	Func(_this, action);
}

bool Hooks::DirectoryPackAccessStrategy__isTrusted(__int64 _this) {
	static auto func = g_Hooks.DirectoryPackAccessStrategy__isTrustedHook->GetFastcall<bool, __int64>();

	static uintptr_t** directoryPackAccessStrategyVtable = 0;

	if (!directoryPackAccessStrategyVtable) {
		uintptr_t sigOffset = FindSignature("48 8D 05 ? ? ? ? 49 89 06 49 8D 76 50");
		int offset = *reinterpret_cast<int*>(sigOffset + 3);
		directoryPackAccessStrategyVtable = reinterpret_cast<uintptr_t**>(sigOffset + offset + 7);
	}

	if (*reinterpret_cast<uintptr_t*>(_this) == (uintptr_t)directoryPackAccessStrategyVtable)
		return true;

	return func(_this);
}

bool Hooks::ReturnTrue(__int64 _this) {
	return true;
}

__int64 Hooks::SkinRepository___loadSkinPack(__int64 _this, __int64 pack, __int64 a3) {
	static auto func = g_Hooks.SkinRepository___loadSkinPackHook->GetFastcall<__int64, __int64, __int64, __int64>();

	// auto res = (*(unsigned __int8 (**)(void))(**(__int64**)(pack + 8) + 48i64))();
	// logF("SkinRepository___loadSkinPack: origin %i, is Trusted: %i", *(int*)((*(__int64*)pack) + 872i64), res);
	*(int*)((*(__int64*)pack) + 872i64) = 2;  // Set pack origin to "2"

	return func(_this, pack, a3);
}

GamerTextHolder* Hooks::toStyledString(__int64 strIn, GamerTextHolder* strOut) {
	static auto func = g_Hooks.toStyledStringHook->GetFastcall<GamerTextHolder*, __int64, GamerTextHolder*>();

	static auto conRequest = reinterpret_cast<__int64>(g_Hooks.ConnectionRequest_createHook->funcPtr);
	if (reinterpret_cast<__int64>(_ReturnAddress()) > conRequest && reinterpret_cast<__int64>(_ReturnAddress()) < conRequest + 10000 && overrideStyledReturn) {
		// Return address is within boundaries of connection request function

		strOut->copyFrom(&styledReturnText);

		return strOut;
	}

	return func(strIn, strOut);
}

__int64 Hooks::InGamePlayScreen___renderLevel(__int64 playScreen, __int64 a2, __int64 a3) {
	static auto func = g_Hooks.InGamePlayScreen___renderLevelHook->GetFastcall<__int64, __int64, __int64, __int64>();
	return func(playScreen, a2, a3);
}

__int64 Hooks::GameMode_attack(GameMode* _this, Entity* ent) {
	static auto func = g_Hooks.GameMode_attackHook->GetFastcall<__int64, GameMode*, Entity*>();
	moduleMgr->onAttack(ent);
	return func(_this, ent);
}

void Hooks::LocalPlayer__updateFromCamera(__int64 a1, Camera* camera, __int64* a3, Entity* a4) {
	static auto func = g_Hooks.LocalPlayer__updateFromCameraHook->GetFastcall<__int64, __int64, Camera*, __int64*, Entity*>();
	auto freecamMod = moduleMgr->getModule<Freecam>();
	freecamMod->camera = camera;
	// camera->nearClippingPlane = 0.000001;
	// camera->farClippingPlane = -5;
	func(a1, camera, a3, a4);
}

bool Hooks::Mob__isImmobile(Entity* ent) {
	static auto func = g_Hooks.Mob__isImmobileHook->GetFastcall<bool, Entity*>();
	static auto freecamMod = moduleMgr->getModule<Freecam>();
	static auto antiImmobileMod = moduleMgr->getModule<AntiImmobile>();
	if (freecamMod->isEnabled())
		return true;
	if (antiImmobileMod->isEnabled() && ent == Game.getLocalPlayer())
		return false;

	return func(ent);
}

void Hooks::Actor__setRot(Entity* _this, Vec2& angle) {
	static auto func = g_Hooks.Actor__setRotHook->GetFastcall<void, Entity*, Vec2&>();
	static auto freelookMod = moduleMgr->getModule<Freelook>();
	static auto freecamMod = moduleMgr->getModule<Freecam>();
	if (_this == Game.getLocalPlayer()) {
		if (freecamMod->isEnabled()) {
			freecamMod->yaw = angle.y;
			angle = {freecamMod->initialViewAngles.x, freecamMod->initialViewAngles.y};
		}
		if (freelookMod->isEnabled()) angle = freelookMod->oldPos;
	}
	func(_this, angle);
}

void Hooks::InventoryTransactionManager__addAction(Player* _this, InventoryAction* action, char a3) {
	static auto func = g_Hooks.InventoryTransactionManager__addActionHook->GetFastcall<void, Player*, InventoryAction*, char>();

#ifdef TEST_DEBUG
	Game.getGuiData()->displayClientMessageF("%sInvSource: %d %d %d %sSlot: %i %sItem counts: %i %i", RED, action->inventorySource.type, action->inventorySource.containerId, action->inventorySource.flags, GREEN, action->slot, BLUE, action->sourceItem.count, action->targetItem.count);
	/*if(/*action.slot == 14 && action.sourceType == 124 && strcmp(targetName, "none") == 0 && *strcmp(srcName, "stone_shovel") == 0){
		std::string tag = "{ench:[{id:9s,lvl:1s}]}";
		action.sourceItem.setUserData(std::move(Mojangson::parseTag(tag)));
	}
	if(/*action.slot == 2 && action.sourceType == 256 && strcmp(srcName, "none") == 0 &&* strcmp(targetName, "stone_shovel") == 0){
		std::string tag = "{ench:[{id:9s,lvl:1s}]}";
		action.targetItem.setUserData(std::move(Mojangson::parseTag(tag)));
	}*/
#endif
	func(_this, action, a3);
}

void Hooks::LevelRendererPlayer__renderNameTags(__int64 a1, __int64 a2, TextHolder* a3, __int64 a4) {
		static auto func = g_Hooks.LevelRendererPlayer__renderNameTagsHook->GetFastcall<void, __int64, __int64, TextHolder*, __int64>();
		static auto nameTagsMod = moduleMgr->getModule<NameTags>();

		if (!nameTagsMod || !nameTagsMod->isEnabled())
			return func(a1, a2, a3, a4);

		std::string text = Utils::sanitize(a3->getText());
		std::size_t found = text.find('\n');

		if (found != std::string::npos)
			text = text.substr(0, found);

		if (nameTagsMod->nameTags.find(text) != nameTagsMod->nameTags.end())
			return;

		return func(a1, a2, a3, a4);
}

float Hooks::getDestroySpeed(Player* _this, Block& block) {
	static auto oFunc = g_Hooks.getDestroySpeedHook->GetFastcall<float, Player*, Block&>();
	static auto instaBreakMod = moduleMgr->getModule<InstaBreak>();

	return instaBreakMod->isEnabled() ? INFINITY : oFunc(_this, block);
}

bool Hooks::Actor_canSee(Entity* _this, Entity& entity) {
	static auto oFunc = g_Hooks.Actor_canSeeHook->GetFastcall<bool, Entity*, Entity&>();
	static auto antiInvisMod = moduleMgr->getModule<AntiInvis>();

	return antiInvisMod->isEnabled() ? true : oFunc(_this, entity);
}

bool Hooks::Actor_shouldRender(Entity* _this) {
	static auto oFunc = g_Hooks.Actor_shouldRenderHook->GetFastcall<bool, Entity*>();
	static auto antiInvisMod = moduleMgr->getModule<AntiInvis>();

	return antiInvisMod->isEnabled() ? true : oFunc(_this);
}

bool Hooks::Actor__isInWall(Entity* ent) {
	static auto func = g_Hooks.ActorisInWallHook->GetFastcall<bool, Entity*>();
	static auto nofallMod = moduleMgr->getModule<NoFall>();

	if (nofallMod->isEnabled() && nofallMod->mode.selected == 4 /*&& Game.getLocalPlayer() == ent*/) {
		return false;
	}

	return func(ent);
}
/*
void Hooks::testFunction(class networkhandler* _this, const void* networkIdentifier, Packet* packet, int a4) {
	auto func = g_Hooks.testHook->GetFastcall<void, networkhandler*, const void*, Packet*, int>();
	static auto test = moduleMgr->getModule<TestModule>();

	if (test->isEnabled()) {
		//if (strcmp(packet->getName()->getText(), "SetTitlePacket") != 0) {
			Game.getClientInstance()->getGuiData()->displayClientMessageF("%s", packet->getName()->getText());
		//}
	}
	if (test->isEnabled() && test->bool1) {
		return;
	}
	moduleMgr->onSendClientPacket(packet);
	func(_this, networkIdentifier, packet, a4);
}*/
