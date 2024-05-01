#include "TestModule.h"
#include "../../../Utils/Logger.h"
#include "../../../Utils/VoxelIntersector.h"
#include "../../DrawUtils.h"
#include "../../../SDK/MatrixStack.h"
#include <deque>
#include <array>
#include <unordered_set>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>			//radians
#include <glm/ext/matrix_transform.hpp>		// perspective, translate, rotate
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../../../Utils/Json.hpp"
#include "../../path/JoePathFinder.h"
#include "../../path/JoeMovementController.h"
#include "../../path/goals/JoeGoal.h"
#include "../../path/goals/JoeGoalXZ.h"
#include "../../ImmediateGui.h"
#include <chrono>  // for std::this_thread::sleep_for()
#include <thread>
#include "../../../Memory/Hooks.h"
//#include "../../../Memory/SlimMem.h"
//#include "../../../Memory/GameData.cpp"
using json = nlohmann::json;


TestModule::TestModule() : IModule(0, Category::MISC, "For testing purposes only!") {
	enum1.addEntry(EnumEntry("1", 1)).addEntry(EnumEntry("2", 2)).addEntry(EnumEntry("3", 3));
	registerFloatSetting("float1", &float1, 0, -10, 10);
	registerIntSetting("int1", &int1, 0, -10, 10);
	registerEnumSetting("Enum1", &enum1, 0);
	registerBoolSetting("bool1", &bool1, true);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "TestModule";
}

bool TestModule::isFlashMode() {
	return false;
}

void TestModule::onEnable() {
	LocalPlayer* player = Game.getLocalPlayer();
	Inventory* inv = player->getSupplies()->inventory;
	if (player != nullptr) {
	}
	//PlayerHotbarPacket packet;
	//packet = PlayerHotbarPacket(1, 10, false);
	//Game.getClientInstance()->loopbackPacketSender->sendToServer(&packet);
}

void TestModule::onTick(GameMode* gm) {
}

void TestModule::onMove(MoveInputHandler* hand){
}

void TestModule::onPreRender(MinecraftUIRenderContext* renderCtx) {
	/* LocalPlayer* player = Game.getLocalPlayer();
	Inventory* inv = player->getSupplies()->inventory;
	Vec2 pos = Vec2(Game.getGuiData()->heightReal, Game.getGuiData()->widthReal);
	pos.x / 2.55;
	pos.y / 2.55;
	if (player != nullptr) {
		for (int i = 0; i <= 35; i++) {
			ItemStack* item = inv->getItemStack(i);
			//if (item->item != nullptr) {
				//std::string itemName = TextHolder(item->getItem()->name).getText();
				DrawUtils::drawItem(item, pos, 10.f, 1.f, false);
				pos.x += 20;
			}
		}
	}
	if (HorionGui.Button("Test Button", Vec2(200, 200), true)) {  // Check if button is pressed. When it gets pressed it sends the message.
		clientMessageF("Test Button Was Clicked");
	}*/
}

void TestModule::onPostRender(MinecraftUIRenderContext* renderCtx) {
}

void TestModule::onSendPacket(Packet* p) {
	if (p->isInstanceOf<PlayerHotbarPacket>()) {
		PlayerHotbarPacket* packet = reinterpret_cast<PlayerHotbarPacket*>(p);
		//packet->dimension = 1;
		//logF("%i", packet->numTransactions);
	}
}

void TestModule::onSendClientPacket(Packet* p) {
	if (p->isInstanceOf<PlayerHotbarPacket>()) {
		PlayerHotbarPacket* packet = reinterpret_cast<PlayerHotbarPacket*>(p);
		//packet->dimension = 1;
		//logF("%s", packet->name);
	}
}

void TestModule::onDisable() {
}

void TestModule::onLevelRender() {
}

void TestModule::onKey(int key, bool isDown, bool& cancel) {
	//Cancel W key for testing to make sure this works
	//if (key == 'W' && isDown) cancel = true;
}