#pragma once
#include "../Horion/DrawUtils.h"

class ColorUtil {
private:
	unsigned __int64 lastMS = getCurrentMs();
	inline static unsigned __int64 getCurrentMs() {
		FILETIME f;
		GetSystemTimeAsFileTime(&f);
		(unsigned long long)f.dwHighDateTime;
		unsigned __int64 nano = ((unsigned __int64)f.dwHighDateTime << 32LL) + (unsigned __int64)f.dwLowDateTime;
		return (nano - 116444736000000000LL) / 10000;
	}

public:
	inline static MC_Color getRainbowColor(float seconds, float saturation, float brightness, long index) {
		float currentHue = (((getCurrentMs() + index) % (int)(seconds * 1000)) / (float)(seconds * 1000));
		float red, green, blue = 0.0f;
		Utils::ColorConvertHSVtoRGB(currentHue, saturation, brightness, red, green, blue);

		return MC_Color(red, green, blue);
	}
};