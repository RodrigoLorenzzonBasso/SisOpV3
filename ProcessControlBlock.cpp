#include "ProcessControlBlock.h"
#include <iostream>

ProcessControlBlock::ProcessControlBlock(int indexPart, int base, int limit)
{
	st = new StateCpu(indexPart, base, limit);
	particao = indexPart;

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