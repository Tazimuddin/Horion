#pragma once

#include <typeinfo>
#include <vector>
#include <optional>
#include <memory>
#include <mutex>
#include <shared_mutex>

#include "../../Memory/GameData.h"

#include "Modules/FollowPathModule.h"
#include "Modules/InventoryCleaner.h"
//#include "Modules/Notifications.h"
//#include "Modules/InfiniteAura.h"
#include "Modules/StackableItem.h"
#include "Modules/InventoryMove.h"
#include "Modules/AntiImmobile.h"
#include "Modules/EditionFaker.h"
#include "Modules/ChestStealer.h"
#include "Modules/ReachDisplay.h"
#include "Modules/AutoSplitter.h"
#include "Modules/OffhandAllow.h"
#include "Modules/ClientTheme.h"
#include "Modules/FontChanger.h"
#include "Modules/VanillaPlus.h"
//#include "Modules/CubeGlide.h"
#include "Modules/TimeChanger.h"
#include "Modules/CrystalAura.h"
#include "Modules/ClickGuiMod.h"
#include "Modules/AutoClicker.h"
#include "Modules/TriggerBot.h"
#include "Modules/RainbowSky.h"
#include "Modules/NoSlowDown.h"
#include "Modules/InstaBreak.h"
#include "Modules/BlockReach.h"
#include "Modules/FullBright.h"
#include "Modules/FastLadder.h"
#include "Modules/AutoSprint.h"
#include "Modules/AutoGapple.h"
#include "Modules/ViewModel.h"
#include "Modules/Arraylist.h"
#include "Modules/Waypoints.h"
#include "Modules/NoHurtcam.h"
#include "Modules/NightMode.h"
#include "Modules/NoFriends.h"
//#include "Modules/Jetpack.h"
#include "Modules/HudModule.h"
//#include "Modules/FastEat.h"
#include "Modules/ChestAura.h"
#include "Modules/BowAimbot.h"
#include "Modules/AutoTotem.h"
#include "Modules/AutoSneak.h"
#include "Modules/AutoArmor.h"
#include "Modules/AntiInvis.h"
#include "Modules/FastStop.h"
#include "Modules/Freelook.h"
#include "Modules/Scaffold.h"
#include "Modules/NoPacket.h"
#include "Modules/Velocity.h"
#include "Modules/NameTags.h"
#include "Modules/MidClick.h"
#include "Modules/HighJump.h"
#include "Modules/Teleport.h"
#include "Modules/AntiVoid.h"
#include "Modules/Reducer.h"
#include "Modules/Compass.h"
#include "Modules/Godmode.h"
#include "Modules/NoSwing.h"
#include "Modules/Spammer.h"
#include "Modules/Freecam.h"
#include "Modules/Crasher.h"
#include "Modules/Breaker.h"
#include "Modules/AntiBot.h"
#include "Modules/AirSwim.h"
#include "Modules/AirJump.h"
#include "Modules/Spider.h"
#include "Modules/Tracer.h"
#include "Modules/NoFall.h"
#include "Modules/Module.h"
#include "Modules/Hitbox.h"
#include "Modules/Aimbot.h"
#include "Modules/Twerk.h"
#include "Modules/Radar.h"
#include "Modules/Teams.h"
#include "Modules/Tower.h"
#include "Modules/Timer.h"
#include "Modules/Reach.h"
#include "Modules/Phase.h"
#include "Modules/Nuker.h"
#include "Modules/NoWeb.h"
#include "Modules/Jesus.h"
#include "Modules/Glide.h"
#include "Modules/Blink.h"
#include "Modules/Xray.h"
#include "Modules/Step.h"
#include "Modules/StorageESP.h"
#include "Modules/Fly.h"
#include "Modules/Killaura.h"
#include "Modules/Derp.h"
#include "Modules/Bhop.h"
#include "Modules/Nbt.h"
#include "Modules/ESP.h"
#include "Modules/selectionHighlight.h"
#include "Modules/NoEntityRender.h"
#include "Modules/Partner.h"
#include "Modules/Notifications.h"
#include "Modules/BlockOutline.h"
#include "Modules/TargetHud.h"
#include "Modules/Speed.h"
#include "Modules/Criticals.h"

#ifdef _DEBUG
#include "Modules/PacketLogger.h"
#include "Modules/TestModule.h"
#endif


class ModuleManager {
private:
	GameData* gameData;
	std::vector<std::shared_ptr<IModule>> moduleList;
	bool initialized = false;
	std::shared_mutex moduleListMutex;

public:
	~ModuleManager();
	ModuleManager(GameData* gameData);
	void initModules();
	void disable();
	void onLoadConfig(void* conf);
	void onSaveConfig(void* conf);
	void onTick(GameMode* gameMode);
	void onAttack(Entity* attackedEnt);
	void onWorldTick(GameMode* gameMode);
	void onKeyUpdate(int key, bool isDown);
	void onKey(int key, bool isDown, bool& shouldCancel);
	void onPreRender(MinecraftUIRenderContext* renderCtx);
	void onPostRender(MinecraftUIRenderContext* renderCtx);
	void onLevelRender();
	void onMove(MoveInputHandler* handler);
	void onPlayerTick(Player* player);
	void onSendPacket(Packet*);
	void onSendClientPacket(Packet*);
	void onBaseTick(Entity*);

	std::shared_lock<std::shared_mutex> lockModuleList() { return std::shared_lock(moduleListMutex); }
	std::unique_lock<std::shared_mutex> lockModuleListExclusive() { return std::unique_lock(moduleListMutex); }
	
	std::shared_mutex* getModuleListLock() { return &moduleListMutex; }

	bool isInitialized() { return initialized; };
	std::vector<std::shared_ptr<IModule>>* getModuleList();

	int getModuleCount();
	int getEnabledModuleCount();

	/*
	 *	Use as follows: 
	 *		IModule* mod = moduleMgr.getModule<NoKnockBack>(); 
	 *	Check for nullptr directly after that call, as Hooks::init is called before ModuleManager::initModules !	
	 */
	template <typename TRet>
	TRet* getModule() {
		if (!isInitialized())
			return nullptr;
		auto lock = lockModuleList();
		for (auto pMod : moduleList) {
			if (auto pRet = dynamic_cast<typename std::remove_pointer<TRet>::type*>(pMod.get())){
				
				return pRet;
			}
		}
		return nullptr;
	};

	// Dont Use this functions unless you absolutely need to. The function above this one works in 99% of cases
	std::optional<std::shared_ptr<IModule>> getModuleByName(const std::string name) {
		if (!isInitialized())
			return nullptr;
		std::string nameCopy = name;
		std::transform(nameCopy.begin(), nameCopy.end(), nameCopy.begin(), ::tolower);
		
		auto lock = lockModuleList();
		for (std::vector<std::shared_ptr<IModule>>::iterator it = moduleList.begin(); it != moduleList.end(); ++it) {
			std::shared_ptr<IModule> mod = *it;
			std::string modNameCopy = mod->getRawModuleName();
			std::transform(modNameCopy.begin(), modNameCopy.end(), modNameCopy.begin(), ::tolower);
			if (modNameCopy == nameCopy)
				return std::optional<std::shared_ptr<IModule>>(mod);
		}
		return std::optional<std::shared_ptr<IModule>>();
	}
};

extern ModuleManager* moduleMgr;
