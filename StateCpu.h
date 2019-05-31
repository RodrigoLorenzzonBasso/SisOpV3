/*
	Classe para guardar informa��es flutuantes da cpu
*/

#ifndef STATE_CPU_H
#define STATE_CPU_H

class StateCpu
{
public:
    StateCpu(int indexPart, int base, int limit);
	
	int* getPc();
	int* getBase();
	int* getLimit();
	int* getIndexPart();
	int* getRegs();
	void incPc();
	int pc;
	int base;
private:


	int limit;
	int indexPart;
	int regs[8] = {0, 0, 0, 0, 0, 0, 0, 0};
};

#endif