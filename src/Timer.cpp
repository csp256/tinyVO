#include "Timer.h"

import <chrono>;

class TimerImpl
{
public:
	TimerImpl()
	{
		Reset();
	}

	void Reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	float Elapsed()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
	}

	float Milliseconds()
	{
		return Elapsed() * 1000.0f;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};

//////////////////////////////////////////

Timer::Timer()
	: _pImpl{new TimerImpl}
{
	reset();
}

Timer::~Timer()
{
	delete(_pImpl);
}

void Timer::reset()
{
	_pImpl->Reset();
}

float Timer::seconds()
{
	return _pImpl->Elapsed();
}

float Timer::milliseconds()
{
	return _pImpl->Milliseconds();
}