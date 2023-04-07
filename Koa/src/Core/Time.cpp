#include "Time.h"

void Time::FrameStart()
{
	auto end = std::chrono::high_resolution_clock::now();
	s_DeltaTime = std::chrono::duration<double>(end - s_Start).count();
	s_Start = std::chrono::high_resolution_clock::now();
}

double Time::DeltaTime()
{
	return s_DeltaTime;
}

double Time::FixedDeltaTime()
{
	return s_FixedDeltaTime;
}