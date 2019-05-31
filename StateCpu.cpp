#include "StateCpu.h"

StateCpu::StateCpu(int indexPart, int base, int limit)
{
	this->indexPart = indexPart;
	this->base = base;
	this->limit = limit;
	this->pc = 0;
}

int* StateCpu::getPc()
{
	return &pc;
}

int* StateCpu::getBase()
{
	return &base;
}

int* StateCpu::getLimit()
{
	return &limit;
}

int* StateCpu::getIndexPart()
{
	return &indexPart;
}

int* StateCpu::getRegs()
{
	return regs;
}

void StateCpu::incPc()
{
	pc++;
}
