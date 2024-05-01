#include "GameData.h"

#include <Windows.h>

#include <set>

#include "../Utils/Logger.h"
#include "../Utils/Utils.h"
#include "Hooks.h"

GameData Game;
bool GameData::keys[0x256];
SlimUtils::SlimMem* GameData::slimMem;

size_t AABBHasher::operator()(const AABB& i) const {
	return Utils::posToHash(i.lower);
}
void GameData::retrieveClientInstance() {
	static uintptr_t clientInstanceOffset = 0x0;
	if (clientInstanceOffset == 0x0) {
		clientInstanceOffset = GetOffsetFromSig("48 89 0D ? ? ? ? 48 89 0D ? ? ? ? 48 85 C0 74 ? 48 8B C8 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 48 8B 0D ? ? ? ? 48 85 C9 74 ? 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28 C3 CC CC CC CC CC 48 83 EC 28 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 28 E9 ? ? ? ? 48 8D 0D", 3);
		logF("Client: %llX", clientInstanceOffset);
	}
	Game.clientInstance = reinterpret_cast<ClientInstance*>(Utils::readPointer<uintptr_t*>(clientInstanceOffset, {0x0, 0x0, 0x48, 0x0}));
#ifdef _DEBUG
	if (Game.clientInstance == 0)
		throw std::exception("Client Instance is 0");
#endif
}

bool GameData::canUseMoveKeys() {
	MinecraftGame* mc = Game.clientInstance->minecraftGame;
	if (mc == nullptr) {
		return false;
	}

	return mc->canUseKeybinds();
}

bool GameData::isKeyDown(int key) {
	return keys[(int)key];
}

bool GameData::isKeyPressed(int key) {
	if (isKeyDown(key)) {
		while (isKeyDown(key))
			Sleep(1);
		return true;
	}
	return false;
}

bool GameData::isRightClickDown() {
	if (Game.hidController == 0)
		return false;
	return Game.hidController->rightClickDown;
}

bool GameData::isLeftClickDown() {
	if (Game.hidController == 0)
		return false;
	return Game.hidController->leftClickDown;
}

bool GameData::isWheelDown() {
	if (Game.hidController == 0)
		return false;
	return Game.hidController->wheelDown;
}

bool GameData::shouldTerminate() {
	return Game.shouldTerminateB;
}

void GameData::terminate() {
	Game.getClientInstance()->minecraft->setTimerSpeed(20.f);
	g_Hooks.entityList.clear();
	Game.shouldTerminateB = true;
}

bool GameData::shouldHide() {
	return Game.shouldHideB;
}

void GameData::hide() {
	Game.shouldHideB = !(Game.shouldHideB);
}

void GameData::updateGameData(GameMode* gameMode) {
	retrieveClientInstance();
	Game.localPlayer = Game.getLocalPlayer();

	if (Game.localPlayer != nullptr && gameMode->player == Game.localPlayer) {
		Game.gameMode = gameMode;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&Game.lastUpdate));

		if (Game.localPlayer != nullptr) {
			GuiData* guiData = Game.clientInstance->getGuiData();
			if (guiData != nullptr) {
				displayMessages(guiData);
			}
		}
	}
}

void GameData::displayMessages(GuiData* guiData) {
	auto vecLock = Logger::GetTextToPrintLock();
	auto* stringPrintVector = Logger::GetTextToPrint();
#ifdef _DEBUG
	int numPrinted = 0;
	std::vector<TextForPrint>::iterator it;
	for (it = stringPrintVector->begin(); it != stringPrintVector->end(); ++it) {
		numPrinted++;
		if (numPrinted > 20) {
			break;
		}

		guiData->displayClientMessageNoSendF("%s%s%s%s", GOLD, it->time, RESET, it->text);
	}
	stringPrintVector->erase(stringPrintVector->begin(), it);
#else
	stringPrintVector->clear();
#endif
	{
		auto lock = std::lock_guard<std::mutex>(Game.textPrintLock);

		auto& stringPrintVector = Game.textPrintList;
		int numPrinted = 0;
		std::vector<std::string>::iterator it;
		for (it = stringPrintVector.begin(); it != stringPrintVector.end(); ++it) {
			numPrinted++;
			if (numPrinted > 20) {
				break;
			}

			guiData->displayClientMessageNoSendF(it->c_str());
		}
		stringPrintVector.erase(stringPrintVector.begin(), it);
	}
}

void GameData::EntityList_tick(EntityList* list) {
	Game.entityList = list;
}

void GameData::setHIDController(HIDController* Hid) {
	Game.hidController = Hid;
}

void GameData::forEachEntity(std::function<void(Entity*, bool)> callback) {
	if (this->localPlayer && this->localPlayer->level) {
		for (const auto& ent : g_Hooks.entityList) if (ent.ent != nullptr && ent.ent->isPlayer()) callback(ent.ent, false); //Only get players from this list
		for (const auto& ent : Game.getLocalPlayer()->level->getMiscEntityList())
			if (ent != nullptr && ent->getEntityTypeId() >= 1 && ent->getEntityTypeId() <= 999999999 && !ent->isPlayer()) callback(ent, false); //get everythign else from this
	}
}

void GameData::forEachPlayer(std::function<void(Entity*, bool)> callback) {
	if (this->localPlayer && this->localPlayer->level) {
		for (const auto& ent : g_Hooks.entityList) if (ent.ent != nullptr && ent.ent->isPlayer()) callback(ent.ent, false); //get all players
	}
}

void GameData::forEachMob(std::function<void(Entity*, bool)> callback) {
	if (this->localPlayer && this->localPlayer->level) {
		for (const auto& ent : Game.getLocalPlayer()->level->getMiscEntityList())
			if (ent != nullptr && ent->getEntityTypeId() >= 1 && ent->getEntityTypeId() <= 999999999 && !ent->isPlayer()) callback(ent, false); //get all entities that are not players
	}
}

void GameData::addChestToList(ChestBlockActor* chest) {
	if (chest == nullptr || !chest->isMainSubchest())
		return;
	AABB chestAabb = chest->getFullAABB();
	std::lock_guard<std::mutex> listGuard(Game.chestListMutex);
	if (Game.chestList.count(chestAabb) > 0)
		return;

	Game.chestList.insert(chestAabb);
}

void GameData::initGameData(const SlimUtils::SlimModule* gameModule, SlimUtils::SlimMem* slimMem, void* hDllInst) {
	Game.gameModule = gameModule;
	Game.slimMem = slimMem;
	Game.hDllInst = hDllInst;
	retrieveClientInstance();

#ifdef _DEBUG
	logF("Base: %llX", Game.getModule()->ptrBase);
	if (Game.clientInstance != nullptr) {
		logF("ClientInstance: %llX", Game.clientInstance);
		logF("LocalPlayer: %llX", Game.getLocalPlayer());
		logF("MinecraftGame: %llX", Game.clientInstance->minecraftGame);
		logF("LevelRenderer: %llX", Game.clientInstance->levelRenderer);
	}
#endif
}

void GameData::log(const char* fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	char message[300];
	vsprintf_s(message, fmt, arg);
	va_end(arg);
	std::unique_lock<std::mutex> lock(Game.textPrintLock);
	Game.textPrintList.emplace_back(message);
}