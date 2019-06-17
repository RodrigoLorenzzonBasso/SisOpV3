#include "ProcessControlBlock.h"
#include <iostream>

ProcessControlBlock::ProcessControlBlock(int indexPart, int base, int limit, int nFrames)
{
	st = new StateCpu(indexPart, base, limit);
	particao = indexPart;
	this->nFrames = nFrames;

	for(int i = 0; i < 64; i++)
	{
		if(i < nFrames)
		{
			tabelaPag[i] = indexPart + i;
			cout << "Atualizando Tabelas: " << tabelaPag[i] << endl;
		}
		else
		{
			tabelaPag[i] = -1;
		}
		
	}

	thisId = id;
	id++;

}

ProcessControlBlock::~ProcessControlBlock()
{
	delete st;
}

StateCpu* ProcessControlBlock::getSt()
{
	return st;
}

int ProcessControlBlock::getParticao()
{
	return particao;
}

int ProcessControlBlock::id = 0;