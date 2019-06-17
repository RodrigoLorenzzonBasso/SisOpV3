/*
	Classe Process Control Block

	guarda o estado da cpu;
*/

#ifndef PROCESS_CONTROL_BLOCK_H
#define PROCESS_CONTROL_BLOCK_H
/// Rodrigo Basso
/// Rodrigo Perozzo

#include "StateCpu.h"
#include <iostream>

using namespace std;

class ProcessControlBlock
{
public:
	ProcessControlBlock(int indexPart, int base, int limit, int nFrames);
	~ProcessControlBlock();
	StateCpu* getSt();
	int getParticao();

	int thisId;
	int nFrames;

	int tabelaPag[64];

	StateCpu* st = nullptr;
	int particao;

private:

	static int id;
};

#endif