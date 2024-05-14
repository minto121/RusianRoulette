#pragma once
class Timer
{
private:
	

public:
	Timer();

	~Timer();

	void Update();

	void Draw() const;

	void WaitTime();

	
	static int FPS;
};

