#include "GameClock.h"

FrameTime GameClock::frameTime;
long double GameClock::deltaTime = 0;
long double GameClock::currentSecondTimePassed = 0;
int GameClock::fps = 0;
int GameClock::curSecondFrames=0;

//long double GameClock::timePassed;


GameClock::GameClock()
{
}

GameClock::~GameClock()
{
}


void GameClock::OnFrameStart()
{
	frameTime.start = chrono::high_resolution_clock::now();
	
}
void GameClock::OnFrameEnd()
{
	frameTime.end = chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<long double>(frameTime.end - frameTime.start).count();
	currentSecondTimePassed += deltaTime;
	if ((int)(currentSecondTimePassed) > 0) {
		currentSecondTimePassed = 0;
		fps = curSecondFrames;
		curSecondFrames = 0;
	}
	curSecondFrames++;
}