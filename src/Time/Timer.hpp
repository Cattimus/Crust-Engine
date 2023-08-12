#pragma once

#include<iostream>
using namespace std;

#include<SDL2/SDL.h>

class Timer
{
private:
	int32_t startTime;
	int32_t endTime;
	bool enabled;

	//callback function for when the timer elapses
	void (*onElapse)(void* args);
	void* args;

	void Init();

public:
	bool autoReset;

	bool Elapsed();
	void Start(int32_t ms);
	void Reset();
	void Stop();
	
	int32_t TimeSinceStarted();
	int32_t TimeRemaining();

	void OnElapse(void (*callback)(void* args), void* args);
	void CheckElapse();
};
