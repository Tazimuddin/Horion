#include "BlockOutline.h"

BlockOutline::BlockOutline() : IModule(0, Category::VISUAL, "read the name") {
	registerFloatSetting("Thickness", &thickness, thickness, 0.f, 1.f);
	registerFloatSetting("Opacity", &opacityVal, opacityVal, 0.f, 1.f);
	registerBoolSetting("Rainbow", &selectRainbow, selectRainbow);
	registerFloatSetting("Red", &rSelect, rSelect, 0.f, 1.f);
	registerFloatSetting("Green", &gSelect, gSelect, 0.f, 1.f);
	registerFloatSetting("Blue", &bSelect, bSelect, 0.f, 1.f);
}

BlockOutline::~BlockOutline() {
}

const char* BlockOutline::getModuleName() {
	return ("BlockOutline");
}

void BlockOutline::onPostRender(MinecraftUIRenderContext* renderCtx) {
	float customHighlight[4];

	customHighlight[0] = rSelect;
	customHighlight[1] = rSelect;
	customHighlight[2] = rSelect;
	customHighlight[3] = 1.f;

	static float rainbowColors[4];
	if (!(Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
		{
			if (rainbowColors[3] < 1) {
				rainbowColors[0] = 0.2f;
				rainbowColors[1] = 0.2f;
				rainbowColors[2] = 1.f;
				rainbowColors[3] = 1;
			}

			Utils::ApplyRainbow(rainbowColors, 0.0015f);
		}  // 0.0015f

		if (Game.getLocalPlayer() != nullptr) {
			float mC = thickness / 2;
			auto pStruct = Game.getLocalPlayer()->level;

			Vec3 hLower = pStruct->block.toVec3t();
			hLower = hLower.floor();
			Vec3 hUpper = pStruct->block.toVec3t();
			hUpper = hUpper.floor();
			hUpper.x += 1.f;
			hUpper.y += 1.f;
			hUpper.z += 1.f;

			if (selectRainbow) {
				int face = pStruct->blockSide;
				int rayType = pStruct->rayHitType;
				if (rayType == 0) {
					DrawUtils::setColor(rainbowColors[0], rainbowColors[1], rainbowColors[2], fOpacity);
					DrawUtils::drawBox(hLower, hUpper, thickness);
				}

				if (faceH) {
					if (face == 1) {
						DrawUtils::setColor(rainbowColors[0], rainbowColors[1], rainbowColors[2], fOpacity);

						// top
						Vec2 a1 = DrawUtils::worldToScreen(Vec3(hUpper.x, hUpper.y, hUpper.z));
						Vec2 a2 = DrawUtils::worldToScreen(Vec3(hUpper.x, hUpper.y, hUpper.z - 1.f));
						// bottom
						Vec2 a3 = DrawUtils::worldToScreen(Vec3(hUpper.x, hUpper.y - 1.f, hUpper.z));
						Vec2 a4 = DrawUtils::worldToScreen(Vec3(hUpper.x, hUpper.y - 1.f, hUpper.z - 1.f));

						// DrawUtils::drawQuad(a1, a2, a3, a4);
					}

					// DrawUtils::drawText(vec2(100.f, 100.f), &std::string(std::to_string(face) + " " + std::to_string(rayType)), MC_Color(255, 0, 0));
				}

			} else {
				int rayType = pStruct->rayHitType;
				if (rayType == 0) {
					DrawUtils::setColor(rSelect, gSelect, bSelect, opacityVal);
					DrawUtils::drawBox(hLower, hUpper, thickness);
				}

				if (faceH) {
				}
			}
		}
	}
}