#pragma once

#include "../Utils/HMath.h"
#include "Tessellator.h"

class Tessellator;

class ScreenContext {
public:
	BUILD_ACCESS(this, float *, color, 0x30);
	BUILD_ACCESS(this, Tessellator *, tessellator, 0xC0);

	inline float *getColorHolder() {
		return color;
	}

	inline Tessellator *getTessellator() {
		return tessellator;
	}
};