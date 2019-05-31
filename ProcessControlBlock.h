/*
	Classe Process Control Block

	guarda o estado da cpu;
*/

#ifndef PROCESS_CONTROL_BLOCK_H
#define PROCESS_CONTROL_BLOCK_H

#include "StateCpu.h"

class ProcessControlBlock
{
public:
	ProcessControlBlock(int indexPart, int base, int limit);
	~ProcessControlBlock();
	StateCpu* getSt();
	int getParticao();

	int thisId;

	StateCpu* st = nullptr;
	int particao;

private:

	static int id;
};

#endif