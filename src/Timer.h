#pragma once

class TimerImpl;

class Timer
{
public:
	Timer();
	~Timer();

	void reset();

	float seconds();

	float milliseconds();

private:
	TimerImpl* _pImpl;
};
