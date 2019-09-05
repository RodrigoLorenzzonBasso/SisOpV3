/// Rodrigo Basso
/// Rodrigo Perozzo

#include "Timer.h"

Timer::Timer()
{
	start = std::chrono::high_resolution_clock::now();
	reset = false;	
	duration = start - start;
}


Timer::~Timer()
{
}

double Timer::timeMillis()
{
	auto flag = std::chrono::high_resolution_clock::now();
	duration = flag - start;
	double ms = duration.count() * 1000.0;

	if (reset == true)
	{
		start = std::chrono::high_resolution_clock::now();
	}

	return ms;
}

bool Timer::getReset()
{
	return reset;
}

void Timer::setReset(bool reset)
{
	this->reset = reset;
}

void Timer::resetTimer()
{
	start = std::chrono::high_resolution_clock::now();
}
