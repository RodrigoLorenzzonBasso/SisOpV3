/// Rodrigo Basso
/// Rodrigo Perozzo

/**
	Classe que implementa o Processador

	implementa a Thread principal do sistema, a ThreadCpu;
	executa as instru��es geradas pela busca(m�todo fetch);
**/

#ifndef CPU_H
#define CPU_H

#include <string>
#include <queue>
#include <iostream>
#include "StateCpu.h"
#include "MicroInstruction.h"
#include "Execution.h"
#include "MemControl.h"
#include "ProcessControl.h"
#include "ProcessControlBlock.h"
#include "Mutex.h"

class CPU
{
public:
    CPU(int tamPart, unsigned int * memoria, MemControl * memoryMaganer);
	void setSt(StateCpu * st);
	MicroInstruction* fetch();
	void incPc();
	int execInst(int *interruptParam, ProcessControlBlock * pcb);
	void THREAD_CPU(ProcessControl * processManager, bool * debug, bool * stop, queue<int> * buffer);

private:
	StateCpu* st = nullptr;
	Execution* ex = nullptr;
	
	unsigned int* memoria;
	int	tamPart;

	bool* stop = nullptr;
	bool* debug = nullptr;

	int interruptFlag;
	int interruptParameter;
};

#endif