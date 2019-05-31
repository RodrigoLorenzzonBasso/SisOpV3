/*
	Classe que implementa cron�metro

	m�todo timeMillis() retorna tempo desde o instanciamento do objeto
*/

#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();
	double timeMillis();
	bool getReset();
	void setReset(bool reset);
	void resetTimer();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start; //std::chrono::time_point<std::chrono::steady_clock>
	std::chrono::duration<double> duration;
	bool reset;
};

#endif