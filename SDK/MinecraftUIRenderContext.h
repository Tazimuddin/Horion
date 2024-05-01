#pragma once
#include "../Utils/HMath.h"
#include "TextHolder.h"
#include <vector>

struct MC_Color;

class FilePath {
private:
	char pad_0x0[0x8];    //0x0000
	TextHolder filePath;  //0x0008
public:
	FilePath(std::string filePath) {
		memset(this, 0, sizeof(FilePath));
		this->filePath.setText(filePath);
	};
};

class TexturePtr {
private:
	char pad_0x0[0x18];  //0x0000
public:
	TextHolder filePath;  //0x0018
private:
	char pad_0x0038[0x20];  //0x0038
};

class Font {
private:
	virtual void destructorFont();
	virtual void unk1();
	virtual void unk2();
	virtual void unk3();
	virtual void unk4();
	virtual void unk5();

public:
	virtual float getLineLength(TextHolder* str, float textSize);  //bool unknown
	virtual float getLineHeight();
};

struct TextMeasureData {
	float textSize;
	int idk;
	bool displayShadow;
	bool bool2;
};

class ResourceLocation;

class MinecraftUIRenderContext {
public:
	class ClientInstance* clientInstance;  // 0x0008
	class ScreenContext* screenContext;    // 0x0010

	float getLineLength(Font* font, TextHolder* str, float textSize, bool unknown) {
		return Utils::CallVFunc<1, float, Font*, TextHolder*, float, bool>(this, font, str, textSize, unknown);
	};
	float getTextAlpha() {
		return Utils::CallVFunc<2, float>(this);
	};
	void setTextAlpha(float alpha) {
		return Utils::CallVFunc<3, void, float>(this, alpha);
	};
	__int64 drawDebugText(const float* pos, TextHolder* text, const float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const uintptr_t* caretMeasureData) {
		return Utils::CallVFunc<4, __int64, const float*, TextHolder*, const float*, float, unsigned int, const TextMeasureData*, const uintptr_t*>(this, pos, text, color, alpha, textAlignment, textMeasureData, caretMeasureData);
	};
	__int64 drawText(Font* font, const float* pos, TextHolder* text, const float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const uintptr_t* caretMeasureData) {
		return Utils::CallVFunc<5, __int64, Font*, const float*, TextHolder*, const float*, float, unsigned int, const TextMeasureData*, const uintptr_t*>(this, font, pos, text, color, alpha, textAlignment, textMeasureData, caretMeasureData);
	};
	void flushText(float timeSinceLastFlush) {
		return Utils::CallVFunc<6, void, float>(this, timeSinceLastFlush);
	};
	__int64 drawImage(const TexturePtr* a2, Vec2 const& ImagePos, Vec2 const& ImageDimension, Vec2 const& uvPos, Vec2 const& uvSize) {
		return Utils::CallVFunc<7, __int64, const TexturePtr*, Vec2 const&, Vec2 const&, Vec2 const&, Vec2 const&>(this, a2, ImagePos, ImageDimension, uvPos, uvSize);
	};
	__int64 drawNineslice(TexturePtr* texturePtr, __int64* ninesliceInfo) {
		return Utils::CallVFunc<8, __int64, TexturePtr*, __int64*>(this, texturePtr, ninesliceInfo);
	};
	__int64 flushImages(MC_Color& color, float opacity, class HashedString& hashedString) {
		return Utils::CallVFunc<9, __int64, MC_Color&, float, class HashedString&>(this, color, opacity, hashedString);
	};
	void drawRectangle(Vec4 const& pos, MC_Color& color, float alpha, int lineWidth) {
		return Utils::CallVFunc<12, void, Vec4 const&, MC_Color&, float, int>(this, pos, color, alpha, lineWidth);
	};
	void fillRectangle(Vec4 const& pos, MC_Color& color, float alpha) {
		return Utils::CallVFunc<13, void, Vec4 const&, MC_Color&, float>(this, pos, color, alpha);
	};
	void setClippingRectangle(Vec4 const& pos) {
		return Utils::CallVFunc<20, void, Vec4 const&>(this, pos);
	};
	void saveCurrentClippingRectangle() {
		return Utils::CallVFunc<22, void>(this);
	};
	void restoreSavedClippingRectangle() {
		return Utils::CallVFunc<23, void>(this);
	};
	TexturePtr* getTexture(TexturePtr* texture, ResourceLocation* resourceLocation, bool iDontFuckingKnowBruhPleaseHelpMeNigga) {
		return Utils::CallVFunc<29, TexturePtr*, TexturePtr*, ResourceLocation*, bool>(this, texture, resourceLocation, iDontFuckingKnowBruhPleaseHelpMeNigga);
	};
};