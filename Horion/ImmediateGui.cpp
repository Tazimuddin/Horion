#include "ImmediateGui.h"

ImmediateGui HorionGui;

ComponentInfo::ComponentInfo(int id) : id(id) {
}

ButtonInfo::ButtonInfo(int id, Vec2 pos, bool centered) : ComponentInfo(id), pos(pos), centered(centered) {
}

ImageButtonInfo::ImageButtonInfo(int id, Vec2 pos, bool centered) : ButtonInfo(id, pos, centered) {
}

void ButtonInfo::calculateSize(const char* txt) {
	std::string str(txt);
	size = {DrawUtils::getTextWidth(&str), DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight()};
}

bool ButtonInfo::isInSelectableSurface(Vec2 mouse) {
	Vec4 surface = getSelectableSurface();
	return surface.contains(&mouse);
}

Vec4 ButtonInfo::getSelectableSurface() {
	if (centered) {
		return {pos.x - padding - size.x / 2,
				pos.y - padding - size.y / 2,
				pos.x + padding + size.x / 2,
				pos.y + padding + size.y / 2};
	} else {
		return {pos.x - padding,
				pos.y - padding,
				pos.x + padding + size.x,
				pos.y + padding + size.y};
	}
}

void ButtonInfo::draw(Vec2 mousePos, const char* label) {
	calculateSize(label);
	auto surface = getSelectableSurface();
	Vec2 textPos = pos;
	std::string str(label);
	if (centered) {
		textPos.x -= DrawUtils::getTextWidth(&str) / 2;
		textPos.y -= DrawUtils::getFont(Fonts::SMOOTH)->getLineHeight() / 2;
	}
	
	DrawUtils::drawText(textPos, &str, MC_Color());
	if (isInSelectableSurface(mousePos)) {  // Mouse hovering over us
		if (DrawUtils::isLeftClickDown) surface = surface.shrink(0.8f);  // shrink the button when pressed
		DrawUtils::fillRectangle(surface, MC_Color(85, 85, 85), 1);
		canClickB = true;
	} else {
		DrawUtils::fillRectangle(surface, MC_Color(12, 12, 12), 1);
		canClickB = false;
	}		
}

void ImageButtonInfo::updateSize(Vec2 size) {
	this->size = size;
}

void ImageButtonInfo::draw(Vec2 mousePos, const char* location) {
	auto surface = getSelectableSurface();
	Vec2 imagePos = pos;
	Vec2 imageSize = size;

	if (centered) {
		imagePos.x -= imageSize.x / 2;
		imagePos.y -= imageSize.y / 2;
	}

	if (isInSelectableSurface(mousePos)) {
		if (DrawUtils::isLeftClickDown) {
			surface = surface.shrink(0.8f);
			imageSize.x *= 0.95f;
			imageSize.y *= 0.95f;

			imagePos.x += imagePos.x * 0.025f;
			imagePos.y += imagePos.y * 0.025f;
		}

		DrawUtils::fillRectangle(surface, MC_Color(85, 85, 85), 0.2f);
		canClickB = true;
	} else {
		//DrawUtils::fillRectangle(surface, MC_Color(12, 12, 12), 1);
		canClickB = false;
	}

	DrawUtils::drawImage(location, imagePos, imageSize, Vec2(0, 0));
}

void ImmediateGui::startFrame() {
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	Vec2 windowSizeReal = Game.getClientInstance()->getGuiData()->windowSizeReal;
	mousePos = *Game.getClientInstance()->getMousePos();
	mousePos = mousePos.div(windowSizeReal);
	mousePos = mousePos.mul(windowSize);

	if (Game.canUseMoveKeys()) {
		mousePos = {-1, -1};
	}
}

bool ImmediateGui::Button(const char* label, Vec2 pos, bool centered) {
	auto id = Utils::getCrcHash(label);
	if (components.find(id) == components.end()) {  // Create new button
		components[id] = std::make_shared<ButtonInfo>(id, pos, centered);
	}
	auto comp = components[id];
	auto button = dynamic_cast<ButtonInfo*>(comp.get());

	button->updatePos(pos);
	button->draw(mousePos, label);
	if (button->canClick() && DrawUtils::shouldToggleLeftClick) {  // Click
		DrawUtils::shouldToggleLeftClick = false;
		return true;
	}

	return false;
}

bool ImmediateGui::ImageButton(const char* location, Vec2 pos, Vec2 size, bool centered) {
	auto id = Utils::getCrcHash(location);
	if (components.find(id) == components.end()) {  // Create new button
		components[id] = std::make_shared<ImageButtonInfo>(id, pos, centered);
	}
	auto comp = components[id];
	auto button = dynamic_cast<ImageButtonInfo*>(comp.get());

	button->updatePos(pos);
	button->updateSize(size);
	button->draw(mousePos, location);
	if (button->canClick() && DrawUtils::shouldToggleLeftClick) {  // Click
		DrawUtils::shouldToggleLeftClick = false;
		return true;
	}

	return false;
}
