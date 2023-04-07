#pragma once
#include <chrono>

class Time
{
private:
	inline static double s_DeltaTime = 0;
	inline static double s_FixedDeltaTime = 0.015f;

	inline static std::chrono::high_resolution_clock::time_point s_Start;
	
	friend class Engine;
private:
	Time() = default;
	static void FrameStart();

public:
	static double DeltaTime();
	static double FixedDeltaTime();

	Time(const Time& other) = delete;
	Time& operator=(const Time& other) = delete;
};