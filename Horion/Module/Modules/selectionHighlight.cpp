#include "../../../SDK/Attribute.h"
#include "../../DrawUtils.h"
#include "HudModule.h"
#include "selectionHighlight.h"

selectionHighlight::selectionHighlight() : IModule(0, Category::VISUAL, "TargetHUD") {
}

selectionHighlight::~selectionHighlight() {
}

const char* selectionHighlight::getModuleName() {
	return ("TargetHUD");
}

static std::vector<Entity*> targetList3;

void findPlayers2(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;
	if (currentEntity == Game.getLocalPlayer())
		return;

	if (!Game.getLocalPlayer()->canAttack(currentEntity, false)) return;
	if (!Game.getLocalPlayer()->isAlive()) return;
	if (!currentEntity->isAlive()) return;
	if (currentEntity->getEntityTypeId() != 319) return;  // Players
	if (!Target::isValidTarget(currentEntity)) return;
	if (currentEntity->getEntityTypeId() == 1677999) return;  // Villager
	if (currentEntity->getEntityTypeId() == 51) return;       // NPC

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 70) {
		targetList3.push_back(currentEntity);
	}
}

struct CompareTargetEnArray {
	bool operator()(Entity* lhs, Entity* rhs) {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void selectionHighlight::onTick(GameMode* gm) {
	// Loop through all our players and retrieve their information
	targetList3.clear();

	Game.forEachEntity(findPlayers2);

	for (auto& i : targetList3) {
		if (!(i->damageTime > 1 && hurttime)) {
			targethud++;
		} else
			targethud = 0;
	}
};

void selectionHighlight::onPreRender(MinecraftUIRenderContext* renderCtx) {
	static auto partner = moduleMgr->getModule<Partner>();
	std::sort(targetList3.begin(), targetList3.end(), CompareTargetEnArray());
	if (Game.isInGame() && !targetList3.empty() && Game.canUseMoveKeys && Game.getLocalPlayer()->canOpenContainerScreen() && targethud >= 1 && targetList3[0]->isPlayer()) {
		// Atributes
		AbsorptionAttribute attribute = AbsorptionAttribute();
		HealthAttribute attribute2 = HealthAttribute();
		float Absorbtion = ((int)targetList3[0]->getAttribute(&attribute)->currentValue);
		float Health = ((int)targetList3[0]->getAttribute(&attribute2)->currentValue);
		float HealthMax = ((int)targetList3[0]->getAttribute(&attribute2)->maximumValue);

		Vec2 res = Game.getClientInstance()->getGuiData()->windowSize;
		LocalPlayer* Player = Game.getClientInstance()->getCILocalPlayer();
		if (Player != nullptr) {
			Vec4 rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) + (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 8.f));  // vec4_t rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) - (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 24.f));
			float rectWidth = rectPos.z - rectPos.x;

			// counter for fade
			counter++;
			if (counter == 100)
				counter--;
			DrawUtils::fillRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
			DrawUtils::drawRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(150, 30, 255), counter / 340.33333f);
			if (partner->Partnered.selected == 0) {
				DrawUtils::fillRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
				DrawUtils::drawRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(150, 30, 255), counter / 340.33333f);
			} else if (partner->Partnered.selected == 1) {
				DrawUtils::fillRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
				DrawUtils::drawRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 255), counter / 340.33333f);
			} else if (partner->Partnered.selected == 2) {
				DrawUtils::fillRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 0, 0), counter / 340.33333f);
				DrawUtils::drawRectangle(Vec4{rectPos.x - 1, rectPos.y - 8, rectPos.z + 1, rectPos.w + 1}, MC_Color(0, 255, 455), counter / 340.33333f);
			}

			std::string targetName;
			targetName = Utils::sanitize(targetList3[0]->getNameTag()->getText());
			targetName = targetName.substr(0, targetName.find('\n'));


			std::string HealthString = std::to_string(((int)Health));
			std::string HealthMaxString = std::to_string(((int)HealthMax));
			std::string distance = "Distance: " + std::to_string((int)(*targetList3[0]->getPos()).dist(*Game.getLocalPlayer()->getPos()));
			std::string healthDisplay = "Health: " + HealthString + "/" + HealthMaxString;
			std::string armor = "Armor: ";
			std::string absorptionDisplay;
			// Absorbtion Bar
			if (Absorbtion > 0) {
				//DrawUtils::drawRectangle(Vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + 1 * rectWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 85), counter / 100.f);
				std::string absorptionString = std::to_string((int)(Absorbtion));
				absorptionDisplay = " Absorption: " + absorptionString;
				float absorptionBarWidth = (Absorbtion / HealthMax) * rectWidth;
				if (!(targetList3[0]->damageTime > 1))
					DrawUtils::fillRectangle(Vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 85), counter / 100.f);
				else
					DrawUtils::fillRectangle(Vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), MC_Color(255, 255, 0), counter / 100.f);
			}

			// The text
			{
				DrawUtils::drawText(Vec2(rectPos.x + (res.x / 900.f), rectPos.y - 17 + (res.y / 35.f)), &targetName, MC_Color(255, 255, 255), 1.f, counter / 100.f);  // name
				DrawUtils::drawText(Vec2(rectPos.x + (res.x / 900.f), rectPos.y - 9 + (res.y / 35.f)), &distance, MC_Color(255, 255, 255), 0.7f, counter / 100.f);    // distance
				DrawUtils::drawText(Vec2(rectPos.x + 35 + (res.x / 900.f), rectPos.y - 4 + (res.y / 35.f)), &absorptionDisplay, MC_Color(255, 255, 85), 0.7f, counter / 100.f);  // absorbtion
				DrawUtils::drawText(Vec2(rectPos.x + (res.x / 900.f), rectPos.y - 4 + (res.y / 35.f)), &healthDisplay, MC_Color(255, 255, 255), 0.7f, counter / 100.f);          // health
				DrawUtils::drawText(Vec2(rectPos.x + (res.x / 900.f), rectPos.y + 1 + (res.y / 35.f)), &armor, MC_Color(255, 255, 255), 0.7f, counter / 100.f);                  // armor
				Vec2 armorPos = Vec2(rectPos.x + (res.x / 35.f), rectPos.y + 0 + (res.y / 35.f));

				static float constexpr opacity = 10;
				float scale = 2 * 0.13f;
				float spacing = scale + 15.f + 2;

				auto* player = reinterpret_cast<LocalPlayer*>(targetList3[0]);

				for (int t = 0; t < 4; t++) {
					ItemStack* stack = player->getArmor(t);
					if (stack->isValid()) {
						DrawUtils::drawItem(stack, Vec2(armorPos), 1, scale, false);
						armorPos.x += scale * spacing;
					}
				}
				PlayerInventoryProxy* supplies = player->getSupplies();
				ItemStack* item = supplies->inventory->getItemStack(supplies->selectedHotbarSlot);
				 if (item->isValid()) DrawUtils::drawItem(item, Vec2(armorPos), opacity, scale, item->isEnchanted());
			}
			DrawUtils::flush();

			// Health Bar
			{
				float healthBarWidth = (Health / HealthMax) * rectWidth;
				if (!(targetList3[0]->damageTime > 1)) {
					DrawUtils::fillRectangle(Vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), MC_Color(0, 200, 0), counter / 100.f);
					// DrawUtils::drawRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + 1 * rectWidth, rectPos.w), MC_Color(0, 255, 0), counter / 100.f);
				} else {
					DrawUtils::fillRectangle(Vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), MC_Color(255, 0, 0), counter / 100.f);
					// DrawUtils::drawRectangle(vec4(rectPos.x + .2f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + 1 * rectWidth, rectPos.w), MC_Color(255, 0, 0), counter / 100.f);
				}
			}
			rectPos.y += res.y / 0.f;
			rectPos.w += res.y / 0.f;
		}
		DrawUtils::flush();
	}
}

void selectionHighlight::onEnable() {


}

void selectionHighlight::onDisable() {
	targetList3.clear();
}
