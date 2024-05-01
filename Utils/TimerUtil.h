#pragma once

class TimerUtil {
public:
	static bool hasTimedElapsed(__int64 time, bool reset);
	static void setDifference(__int64 difference);
	static bool hasTimePassed(__int64 ms);
	static __int64 getElapsedTime1();
	static bool elapsed(__int64 ms);
	static __int64 getElapsedTime();
	static __int64 getDifference();
	static __int64 getCurrentMs();
	static __int64 getTime();
	static void resetTime();
	static void reset2();
	static void reset1();

	TimerUtil() = default;
};