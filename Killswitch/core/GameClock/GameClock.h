#pragma once

#include <string>
#include <iostream>
#include <chrono>

using namespace std;

/**
* Holds time when previous frame started and ended as 'chrono::time_point<chrono::steady_clock>'
*/
struct FrameTime {
	chrono::time_point<chrono::steady_clock> start;
	chrono::time_point<chrono::steady_clock> end;
};

class GameClock
{
private:
	/**
	* Holds time when previous frame started and ended
	*/
	static FrameTime frameTime;
	/**
	* Holds time that passed in currently active second. Value can be from 0 to 1. When it reaches 1 then it resets back to 0.
	*/
	static long double currentSecondTimePassed;
	/**
	* Number of frames for currently active second. Updates every frame.
	*/
	static int curSecondFrames;
public:
	/**
	* Time difference between start and end of a previous frame.
	*/
	static long double deltaTime;
	/**
	* Number of frames that were captured in previous second. Updates every 1 second(every time currentSecondTimePassed resets back to 0).
	*/
	static int fps;


public:
	GameClock();
	~GameClock();
	/**
	* Called at the very beginning of a frame.
	* Sets frame start time to current time.
	*/
	static void OnFrameStart();
	/**
	* Called at the very end of a frame.
	* Sets frame end time to current time and calculates delta time.
	* Increments currentSecondTimePassed by delta time.
	* If sign value of currentSecondTimePassed > 0, set currentSecondTimePassed to 0 and update fps value to amount of fps calculated in previous second.
	* Increments frame by one.
	*/
	static void OnFrameEnd();
};

