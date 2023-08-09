#pragma once

#include<iostream>
using namespace std;

#include<SDL2/SDL.h>

class Timer
{
private:
	int32_t startTime;
	int32_t endTime;

public:
	bool autoReset;

	bool Elapsed();
	void Set(int32_t ms);
	void Reset();
	void OnElapse();
	int32_t TimeSinceStarted();
	int32_t TimeRemaining();
};
