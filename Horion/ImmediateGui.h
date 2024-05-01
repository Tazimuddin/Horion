#pragma once

#include <map>

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "DrawUtils.h"

class ComponentInfo {
public:
	ComponentInfo(int id);
	virtual ~ComponentInfo(){};

protected:
	unsigned int id;
};

class ButtonInfo : public ComponentInfo {
protected:
	Vec2 pos;
	Vec2 size;
	bool centered;
	float padding = 3.f;
	bool canClickB = false;

public:
	ButtonInfo(int id, Vec2 pos, bool centered = false);
	virtual ~ButtonInfo(){};

	void calculateSize(const char*);
	bool isInSelectableSurface(Vec2 mouse);
	Vec4 getSelectableSurface();
	virtual void draw(Vec2 mousePos, const char* label);
	bool canClick() { return canClickB; };
	void updatePos(Vec2 pos) { pos = pos; }
	
};

class ImageButtonInfo : public ButtonInfo {
public:
	ImageButtonInfo(int id, Vec2 pos, bool centered = false);
	virtual ~ImageButtonInfo(){};

	virtual void draw(Vec2 mousePos, const char* location) override;
	void updateSize(Vec2 size);
};

class ImmediateGui {
private:
	Vec2 mousePos;
	std::map<unsigned int, std::shared_ptr<ComponentInfo>> components;

public:
	void startFrame();
	bool Button(const char* label, Vec2 pos, bool centered = false);
	bool ImageButton(const char* location, Vec2 pos, Vec2 size, bool centered = false);
};

extern ImmediateGui 
Gui;