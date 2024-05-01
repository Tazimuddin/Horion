#include "HudModule.h"

#include "../../../Utils/ClientColors.h"
#include "../../DrawUtils.h"
#include "../ModuleManager.h"

HudModule::HudModule() : IModule(0, Category::CLIENT, "Displays things like the ArrayList/TabGUI.") {
	//registerBoolSetting("TabGui", &tabgui, tabgui);
	registerBoolSetting("ClickToggle", &clickToggle, clickToggle);
	//registerBoolSetting("Watermark", &watermark, watermark);
	//registerBoolSetting("Coordinates", &coordinates, coordinates);
	//registerBoolSetting("Show Keybinds", &keybinds, keybinds);
	//registerBoolSetting("Show ArmorHUD", &displayArmor, displayArmor);
	//registerBoolSetting("Keystrokes", &keystrokes, keystrokes);
	registerBoolSetting("Show FPS", &fps, fps);
	//registerBoolSetting("Show CPS", &cps, cps);
	//registerBoolSetting("Always show", &alwaysShow, alwaysShow);
	registerFloatSetting("Array Scale", &scale, scale, 0.5f, 1.5f);
}

HudModule::~HudModule() {
}

const char* HudModule::getModuleName() {
	return "HUD";
}

void HudModule::drawKeystroke(char key, const Vec2& pos) {
	std::string keyString = Utils::getKeybindName(key);
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	/*if (key == *input->forwardKey) {
		Vec4 rectPos(
			pos.x,
			pos.y,
			pos.x + 20.f,
			pos.y + 20.f);
		Vec2 textPos(
			(rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f) + 0.2f,
			rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);
		if (ClientThemes->Theme.selected == 1) {
			DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color(28, 50, 77) : MC_Color(13, 29, 48), 1.f);
		} else {
			DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? MC_Color(85, 85, 85) : MC_Color(12, 12, 12), 1.f);
		}
		DrawUtils::drawText(textPos, &keyString, MC_Color(255, 255, 255), 1.f, 1.f);
	}*/
	if (key == *input->spaceBarKey) {
		keyString = "-";
		Vec4 rectPos(pos.x, pos.y, pos.x + 64.f, pos.y + 15.f);
		Vec2 textPos((rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f), rectPos.y + 7.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? ClientColors::keyStrokeDownColor : ClientColors::keyStrokeUpColor, 1.f);
		DrawUtils::drawText(textPos, &keyString, MC_Color(255, 255, 255), 1.f, 1.f);
	} else {
		Vec4 rectPos(pos.x, pos.y, pos.x + ((key == *input->spaceBarKey) ? 64.f : 20.f), pos.y + ((key == *input->spaceBarKey) ? 15.f : 20.f));
		Vec2 textPos((rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f), rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);

		DrawUtils::fillRectangle(rectPos, GameData::isKeyDown(key) ? ClientColors::keyStrokeDownColor : ClientColors::keyStrokeUpColor, 1.f);
		DrawUtils::drawText(textPos, &keyString, MC_Color(255, 255, 255), 1.f, 1.f);
	}
}

void HudModule::drawMouseKeystroke(Vec2 pos, std::string keyString) {
	Vec4 rectPos(pos.x, pos.y + 2, pos.x + 31.f, pos.y + 22.f);
	if (keyString == "LMB")
		DrawUtils::fillRectangle(rectPos, GameData::isLeftClickDown() ? ClientColors::keyStrokeDownColor : ClientColors::keyStrokeUpColor, 1.f);
	else if (keyString == "RMB")
		DrawUtils::fillRectangle(rectPos, GameData::isRightClickDown() ? ClientColors::keyStrokeDownColor : ClientColors::keyStrokeUpColor, 1.f);

	Vec2 textPos((rectPos.x + (rectPos.z - rectPos.x) / 2) - (DrawUtils::getTextWidth(&keyString) / 2.f), rectPos.y + 10.f - DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2.f);
	DrawUtils::drawText(textPos, &keyString, MC_Color(255, 255, 255), 1.f, 1.f);
}

void HudModule::onPostRender(MinecraftUIRenderContext* renderCtx) {
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	float f = 10.f * scale;
	std::string tempStr("Movement");
	float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
	float startY = tabgui ? 7 * f : 0.f;

	{  // FPS
		if (!(Game.getLocalPlayer() == nullptr || !fps)) {
			std::string fpsText = "FPS: " + std::to_string(Game.getFPS());
			Vec4 rectPos = Vec4(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			Vec2 textPos = Vec2(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::drawText(textPos, &fpsText, MC_Color(255, 255, 255), scale);

			startY += f;
		}
	}

	{  // CPS
		if (!(Game.getLocalPlayer() == nullptr || !cps)) {
			std::string cpsText = "CPS: " + std::to_string(Game.getLeftCPS()) + " - " + std::to_string(Game.getRightCPS());
			Vec4 rectPos = Vec4(2.5f, startY + 5.f * scale, len, startY + 15.f * scale);
			Vec2 textPos = Vec2(rectPos.x + 1.5f, rectPos.y + 1.f);
			DrawUtils::fillRectangle(rectPos, ClientColors::cpsBackgroundColor, 1.f);
			DrawUtils::drawText(textPos, &cpsText, MC_Color(150, 30, 255), scale);

			startY += f;
		}
	}

	{  // Coordinates
		if (!(Game.getLocalPlayer() == nullptr || !coordinates)) {
			Vec3* pos = Game.getLocalPlayer()->getPos();
			std::string coords = std::string("X: ") + std::to_string((int)floorf(pos->x)) + std::string("\nY: ") + std::to_string((int)floorf(pos->y)) + std::string("\nZ: ") + std::to_string((int)floorf(pos->z));

			Vec4 rectPos = Vec4(2.5f, startY + 5.f * scale, len, startY + 35.f * scale);
			Vec2 textPos = Vec2(rectPos.x + 1.5f, rectPos.y + 1.f);

			DrawUtils::fillRectangle(rectPos, ClientColors::coordinatesBackgroundColor, 1.f);
			DrawUtils::drawText(textPos, &coords, MC_Color(150, 30, 255), scale);
		}
	}

	{  // ArmorHUD

		if (!(Game.getLocalPlayer() == nullptr || !displayArmor || !GameData::canUseMoveKeys())) {
			static float constexpr scale = 1.f;
			static float constexpr opacity = 0.75f;
			static float constexpr spacing = scale + 15.f;
			LocalPlayer* player = Game.getLocalPlayer();
			float x = windowSize.x / 2.f + 5.f;
			float y = windowSize.y - 57.5f;
			for (int i = 0; i < 4; i++) {
				ItemStack* stack = player->getArmor(i);
				if (stack->isValid()) {
					DrawUtils::drawItem(stack, Vec2(x, y), opacity, scale, stack->isEnchanted());
					x += scale * spacing;
				}
			}
			PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
			ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
			if (item->isValid())
				DrawUtils::drawItem(item, Vec2(x, y), opacity, scale, item->isEnchanted());
		}
	}

	{  // Keystrokes
		if (!(Game.getLocalPlayer() == nullptr || !keystrokes || !GameData::canUseMoveKeys())) {
			GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
			HudModule::drawKeystroke(*input->forwardKey, Vec2(32.f, windowSize.y - 84));
			HudModule::drawKeystroke(*input->leftKey, Vec2(10.f, windowSize.y - 62));
			HudModule::drawKeystroke(*input->backKey, Vec2(32.f, windowSize.y - 62));
			HudModule::drawKeystroke(*input->rightKey, Vec2(54.f, windowSize.y - 62));
			HudModule::drawKeystroke(*input->spaceBarKey, Vec2(10.f, windowSize.y - 40));
			HudModule::drawMouseKeystroke(Vec2(10.f, windowSize.y - 25), "LMB");
			HudModule::drawMouseKeystroke(Vec2(43.f, windowSize.y - 25), "RMB");
		}
	}
}