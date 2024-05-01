#include "Compass.h"

#include "../ModuleManager.h"

Compass::Compass() : IModule(0, Category::CUSTOM, "Compass.") {
	registerFloatSetting("Opacity", &opacity, opacity, 0.1f, 1);
	registerIntSetting("Range", &range, range, 45, 180);
	registerBoolSetting("Show Waypoints", &showWaypoints, showWaypoints);
}

Compass::~Compass() {
}

const char* Compass::getModuleName() {
	return "Compass";
}

void Compass::onPreRender(MinecraftUIRenderContext* renderCtx) {
	LocalPlayer* player = Game.getLocalPlayer();

	if (player == nullptr || !GameData::canUseMoveKeys()) return;

	static auto wpMod = moduleMgr->getModule<Waypoints>();

	auto extraPoints = std::multimap<int, std::string>{};

	if (showWaypoints) {
		auto waypoints = wpMod->getWaypoints();
		int curDim = player->dimension->dimensionId;
		auto playerInterpPos = player->getPosOld()->lerp(player->getPos(), DrawUtils::getLerpTime());
		for (auto it = waypoints->begin(); it != waypoints->end(); it++) {
			if (it->second.dimension != curDim)
				continue;
			int angle = (int)round(playerInterpPos.CalcAngle(it->second.pos).y + 180.0f) % 360;
			if (angle < 0) angle += 360;

			extraPoints.insert(std::make_pair(angle, it->first));
		}
	}

	std::vector<Vec2> stacking{};

	const int deg = (int)(player->getActorHeadRotationComponent()->rot.y + 180);
	const float degSubOffset = 0;  // -fmodf(player->getActorHeadRotationComponent()->rot.y, 1)
	const float sCenter = Game.getGuiData()->widthGame / 2;

	for (int off = -range; off <= range; off++) {
		int oDeg = (deg + off) % 360;
		if (oDeg < 0) oDeg += 360;

		const float xOff = sCenter + off + degSubOffset;
		constexpr float fadeOutPos = 0.25f;
		constexpr float centerCutoff = 5, centerFadeout = 10;
		float majorOpacity = opacity;  // big compass text
		float minorOpacity = majorOpacity;   // minor features, degree numbers

		// Fading logic
		{
			if ((range - abs(off)) < range * fadeOutPos)  // Far from center
				minorOpacity = majorOpacity = lerp(0, opacity, (range - abs(off)) / (range * fadeOutPos));
			else if (abs(off) < centerFadeout)  // Close to center
				minorOpacity = lerp(0, opacity, (abs(off) - centerCutoff) / (centerFadeout - centerCutoff));
		}

		switch (oDeg) {
		case 0:
			drawCenteredText(Vec2(xOff, 30.f), "N", 1, majorOpacity);
			break;
		case 45:
			drawCenteredText(Vec2(xOff, 30.f), "NE", 1, majorOpacity);
			break;
		case 90:
			drawCenteredText(Vec2(xOff, 30.f), "E", 1, majorOpacity);
			break;
		case 135:
			drawCenteredText(Vec2(xOff, 30.f), "SE", 1, majorOpacity);
			break;
		case 180:
			drawCenteredText(Vec2(xOff, 30.f), "S", 1, majorOpacity);
			break;
		case 225:
			drawCenteredText(Vec2(xOff, 30.f), "SW", 1, majorOpacity);
			break;
		case 270:
			drawCenteredText(Vec2(xOff, 30.f), "W", 1, majorOpacity);
			break;
		case 315:
			drawCenteredText(Vec2(xOff, 30.f), "NW", 1, majorOpacity);
			break;
		}
		auto result = extraPoints.equal_range(oDeg);
		for (auto it = result.first; it != result.second; it++) {
			std::string pName = it->second;
			std::transform(pName.begin(), pName.end(), pName.begin(), ::toupper);

			Vec2 pos = Vec2(xOff, 31.f);

			int overlapping = 0;
			const float tSize = 0.75f;
			const float tWidth = DrawUtils::getTextWidth(&pName, tSize);
			pos.x -= tWidth / 2;
			const Vec2 myTextRange = Vec2(pos.x, pos.x + tWidth); 
			for (const Vec2 otherTextRange : stacking) {
				// Check if other text overlaps us
				if (myTextRange.x < otherTextRange.y && otherTextRange.x < myTextRange.y) {
					overlapping++;
				}
			}
			stacking.push_back(myTextRange);
			pos.y += 5 * (overlapping + 1);
			DrawUtils::drawText(pos, &pName, MC_Color(255, 255, 255), tSize, majorOpacity);
		}

		if (off != 0 && minorOpacity > 0) {
			if ((oDeg % 15) != 0) {
				if ((oDeg % 5) == 0) {
					DrawUtils::fillRectangle(Vec4(xOff - 0.25f, 16, xOff + 0.25f, 19), MC_Color(255, 255, 255), minorOpacity);
				}
				continue;
			}

			// Bigger line with degree displayed
			DrawUtils::fillRectangle(Vec4(xOff - 0.5f, 15, xOff + 0.5f, 20), MC_Color(255, 255, 255), minorOpacity);
			drawCenteredText(Vec2(xOff, 20.f), std::to_string(oDeg), 0.75f, minorOpacity);
		}
	}

	// Center line
	DrawUtils::fillRectangle(Vec4(sCenter - 0.5f, 15, sCenter + 0.5f, 25), MC_Color(255, 255, 255), opacity);
	drawCenteredText(Vec2(sCenter, 25.f), std::to_string(deg), 0.75f, opacity);
	DrawUtils::flush();
}

void Compass::drawCenteredText(Vec2 pos, std::string text, float size, float textOpacity) {
	pos.x -= DrawUtils::getTextWidth(&text, size) / 2;
	DrawUtils::drawText(pos, &text, MC_Color(255, 255, 255), size, textOpacity);
}
