#pragma once

class Weather {
private:
	char pad_0000[56];  //0x0000
public:
	bool isRaining;  //0x0038
private:
	char pad_0039[11];  //0x0039
public:
	bool isLightning;  //0x0044
private:
	char pad_0045[3];  //0x0045
public:
	float lightningLevel;  //0x0048
};