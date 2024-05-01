#include "TimerUtil.h"

#include <Windows.h>

#include <chrono>
#include <ctime>
#include <iostream>

#include "../../Utils/Logger.h"

__int64 lastMS = TimerUtil::getCurrentMs();
__int64 ms;
__int64 prevMS = 0;
__int64 timeMS = -1;

__int64 TimerUtil::getCurrentMs() {
	FILETIME f;
	GetSystemTimeAsFileTime(&f);
	(long long)f.dwHighDateTime;
	__int64 nano = ((__int64)f.dwHighDateTime << 32LL) + (__int64)f.dwLowDateTime;
	return (nano - 116444736000000000LL) / 10000;
}

bool TimerUtil::hasTimePassed(__int64 ms) {
	return getCurrentMs() >= timeMS + ms;
}

__int64 TimerUtil::getTime() {
	return getCurrentMs();
}

void TimerUtil::reset2() {
	prevMS = getTime();
}

__int64 TimerUtil::getDifference() {
	return getTime() - prevMS;
}

void TimerUtil::setDifference(__int64 difference) {
	prevMS = getTime() - difference;
}

void TimerUtil::resetTime() {
	lastMS = getCurrentMs();
	timeMS = getCurrentMs();
}

__int64 TimerUtil::getElapsedTime1() {
	return (getCurrentMs() - timeMS);
}

bool TimerUtil::hasTimedElapsed(__int64 time, bool reset) {
	if (getCurrentMs() - lastMS > time) {
		if (reset)
			resetTime();
		return true;
	}
	return false;
}

void TimerUtil::reset1() {
	ms = getCurrentMs();
}

bool TimerUtil::elapsed(__int64 milliseconds) {
	return (getCurrentMs() - ms) > milliseconds;
}

__int64 TimerUtil::getElapsedTime() {
	return getCurrentMs() - ms;
}