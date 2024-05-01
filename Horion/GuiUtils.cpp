#include "GuiUtils.h"

void GuiUtils::drawCrossLine(Vec2 pos, MC_Color col, float lineWidth, float crossSize, bool secondCross) {
	crossSize /= 2;
	DrawUtils::setColor(col.r, col.g, col.b, col.a);
	//float MidX = (pos.z + pos.x) / 2;
	//float MidY = (pos.y + pos.w) / 2;
	DrawUtils::drawLine(Vec2(pos.x - crossSize, pos.y), Vec2(pos.x + crossSize, pos.y), lineWidth);
	if (secondCross)
		DrawUtils::drawLine(Vec2(pos.x, pos.y - crossSize), Vec2(pos.x, pos.y + crossSize), lineWidth);
}
