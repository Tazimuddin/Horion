#include "ReachDisplay.h"

#include "../../DrawUtils.h"
#include "../../../Utils/ClientColors.h"

ReachDisplay::ReachDisplay() : IModule(0, Category::PLAYER, "Displays your reach.") {
	registerFloatSetting("Scale", &this->scale, this->scale, 0.5f, 1.5f);
}

ReachDisplay::~ReachDisplay() { }

const char* ReachDisplay::getModuleName() {
	return "ReachDisplay";
}

void ReachDisplay::onEnable() {
	this->currReach = 0.0f;
	this->ticks = 0;

	this->reachStr = (char*)malloc(6);
	sprintf(this->reachStr, "0.0");
}

void ReachDisplay::onTick(GameMode* gm) {
	if (Game.getLocalPlayer() == nullptr) return;

	this->ticks++;

	if (GameData::isLeftClickDown() && Game.getLocalPlayer()->level->hasEntity() != 0) {
		Entity* entity = Game.getLocalPlayer()->level->getEntity();

		if (entity->damageTime > 0) {
			this->ticks = 0;
			this->currReach = (*entity->getPos()).dist(*Game.getLocalPlayer()->getPos());

			sprintf(this->reachStr, "%.2f", this->currReach);
		}
	}
}

void ReachDisplay::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (Game.getLocalPlayer() == nullptr) return;

	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

	if (this->ticks >= 80 && this->currReach > 0.0f) {
		this->currReach = 0.0f;

		sprintf(this->reachStr, "0.0");
	}

	std::string reachDisplay = std::string("Reach: ") + std::string(this->reachStr);

	float len = DrawUtils::getTextWidth(&reachDisplay, this->scale) + 7.f;
	float height = DrawUtils::getFontHeight(this->scale) + 7.f;
	float y = windowSize.y - height - 2.f;

	Vec4 rectPos = Vec4(2.5f, y + 5.f * this->scale, len, y + 15.f * this->scale);
	Vec2 textPos = Vec2(rectPos.x + 1.5f, rectPos.y + 1.f);
	DrawUtils::fillRectangle(rectPos, ClientColors::fpsBackgroundColor, 1.f);
	DrawUtils::drawText(textPos, &reachDisplay, MC_Color(200, 200, 200), this->scale);
}

void ReachDisplay::onDisable() {
	free(this->reachStr);
}
