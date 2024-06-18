#include "Timer.h"
#include "DxLib.h"
#include <math.h>


int Timer::FPS;


Timer::Timer()
{
	
	FPS = 0;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	WaitTime();
}

void Timer::Draw() const
{
	DrawFormatString(0, 20, 0xffffff, "fps:%d", FPS);
	
}

void Timer::WaitTime()
{
	FPS++;
	if (FPS == 400) 
	{
		
		FPS = 0;
	}
}
