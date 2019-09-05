/// Rodrigo Basso
/// Rodrigo Perozzo

/*
	Gerente de Processos

	implementa criacao/destruicao de processos;
	funcionamento interno para gerenciamento dos processos atraves
	de uma fila de processos(readyQueue);
	ThreadTimer para escalonamento de processos;
*/

#ifndef PROCESSCONTROL_H
#define PROCESSCONTROL_H

#include <queue>
#include <vector>
#include <iostream>
#include "MemControl.h"
#include "ProcessControlBlock.h"
#include "Program.h"
#include "Timer.h"
#include "Request.h"
#include "Mutex.h"

using namespace std;

class ProcessControl
{
	public:
		ProcessControl(unsigned int *memoria, int tamPart);
		~ProcessControl();
		ProcessControlBlock* createProcess(Program * p);
		int deleteProcess(ProcessControlBlock* pcb);
		void saveContext(ProcessControlBlock* pcb);
		void restoreContext(ProcessControlBlock* pcb);
		void timerControl();
		ProcessControlBlock* getPcbRodando();
		bool isInterrupted();
		MemControl* getMemoryManager();
		void THREAD_TIMER(bool * debug, bool * stop);

		vector<ProcessControlBlock*>* blockedQueue = nullptr;
		queue<Request*>* requestQueue = nullptr;
		queue<ProcessControlBlock*>* readyQueue = nullptr;
		void mudaPcbRodando(ProcessControlBlock* newPcb);

		vector<ProcessControlBlock*>* pcbList = nullptr;

	private:


		ProcessControlBlock* pcbRodando = nullptr;
		MemControl* memoryManager = nullptr;
		Timer* timer = nullptr;
		int nProcessos;
		bool interrupted;
		double timeSliceMS;
		int tamFrame;
		bool* debug = nullptr;
		bool* stop = nullptr;
};

#endif