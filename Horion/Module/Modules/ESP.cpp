#include "../../../Utils/Target.h"
#include "ESP.h"
ESP::ESP() : IModule(0, Category::VISUAL, "Outlines players") {
	// registerBoolSetting("Rainbow", &doRainbow, doRainbow);
	mode = SettingEnum(this)
			   .addEntry(EnumEntry("Normal", 0))
			   .addEntry(EnumEntry("Hitbox", 1))
			   .addEntry(EnumEntry("2D", 2));
	registerEnumSetting("Mode", &mode, 0);
	registerBoolSetting("Mob", &mobs, mobs);
	registerBoolSetting("Items", &itemESP, itemESP);
}

const char* ESP::getModuleName() {
	return "ESP";
}

static float rcolors[4];

void drawESP(Entity* ent) {
	float width = 0.f;
	float height = 0.f;
	float yOffset = 0.f;

	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	float distance = (*player->getPos()).dist(*ent->getPos());

	float scaleFactor = 0.02f;

	float espSize = 0.05f;

	float r = 0.9f;
	float g = 0.2f;
	float b = 0.2f;
	float alpha = 1.0f;

	DrawUtils::setColor(r, g, b, alpha);
	DrawUtils::drawEntityBox(ent, espSize);
}

void doRenderStuffS(Entity* ent, bool isRegularEntity) {
	static auto esp = moduleMgr->getModule<ESP>();

	auto player = Game.getLocalPlayer();
	// if (ent->timeSinceDeath > 0) return;

	if (Target::isValidTarget(ent)) {
		DrawUtils::setColor(255, 255, 255, fmax(0.1f, fmin(1.f, 15 / (ent->damageTime + 1))));
	} else if (esp->mobs) {
		if (ent->getNameTag()->getTextLength() <= 1 && ent->getEntityTypeId() == 63)
			return;

		if (ent->isInvisible())
			return;

		if (!Game.getLocalPlayer()->canAttack(ent, false))
			return;

		DrawUtils::setColor(255, 255, 255, fmax(0.1f, 5 / fmin(1.f, 5 / (ent->damageTime + 1))));
	} else if (esp->itemESP) {
		if (ent->getEntityTypeId() == 64) {
			DrawUtils::setColor(255, 255, 255, 1);
		} else {
			return;
		}
	} else {
		return;
	}

	if (esp->mode.selected == 2)
		DrawUtils::draw2D(ent, fmax(0.5f, 0.5f / fmax(0.f, (*player->getPos()).dist(*ent->getPos()) * 1.f)));
	else
		DrawUtils::drawEntityBox(ent, fmax(0.5f, 0.5f / fmax(0.f, (*player->getPos()).dist(*ent->getPos()))));
}
float rcolorrs[4];
float Outline = 0;
void ESP::onLevelRender() {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	if (doRainbow) {
		DrawUtils::setColor(255, 255, 255, 1);
	} else
		DrawUtils::setColor(1.f, 1.f, 1.f, 1);
}

void ESP::onPreRender(MinecraftUIRenderContext* renderCtx) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	if (Game.canUseMoveKeys()) Game.forEachEntity(doRenderStuffS);
	LocalPlayer* localPlayer = Game.getLocalPlayer();
};

