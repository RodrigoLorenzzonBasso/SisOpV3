/// Rodrigo Basso
/// Rodrigo Perozzo

#include "Execution.h"

Execution::Execution(unsigned int * memoria, MemControl * gerente)
{
    this->memoria = memoria;
	this->gerente = gerente;
}

void Execution::execute(MicroInstruction * inst, int* pc, int* regs, int* interruptFlag, int *interruptParameter, ProcessControlBlock * pcb)
{

	if (inst->getInst() == "JMP")
	{
		*pc = inst->getImm();
	}
	else if (inst->getInst() == "JMPI")
	{
		*pc = regs[inst->getR1()];
	}

	else if (inst->getInst() == "JMPIG")
	{
		if (regs[inst->getR2()] > 0)
		{
			*pc = regs[inst->getR1()];
		}
	}
	else if (inst->getInst() == "JMPIL")
	{
		if (regs[inst->getR2()] < 0)
		{
			*pc = regs[inst->getR1()];
		}
	}
	else if (inst->getInst() == "JMPIE")
	{
		if (regs[inst->getR2() == 0])
		{
			*pc = regs[inst->getR1()];
		}
	}
	else if (inst->getInst() == "ADDI")
		regs[inst->getR1()] += inst->getImm();
	else if (inst->getInst() == "SUBI")
		regs[inst->getR1()] -= inst->getImm();
	else if (inst->getInst() == "ANDI")
		regs[inst->getR1()] &= inst->getImm();
	else if (inst->getInst() == "ORI")
		regs[inst->getR1()] |= inst->getImm();
	else if (inst->getInst() == "LDI")
		regs[inst->getR1()] = inst->getImm();
	else if (inst->getInst() == "LDD")
	{
		int endFis = gerente->translate(inst->getImm(), pcb);
		regs[inst->getR1()] = memoria[endFis];
	}
	else if (inst->getInst() == "STD")
	{
		int endFis = gerente->translate(inst->getImm(), pcb);
		memoria[endFis] = regs[inst->getR1()];
	}
    else if(inst->getInst() == "ADD")
        regs[inst->getR1()] += regs[inst->getR2()];
    else if(inst->getInst() == "SUB")
        regs[inst->getR1()] -= regs[inst->getR2()];
    else if(inst->getInst() == "MULT")
        regs[inst->getR1()] *= regs[inst->getR2()];
    else if(inst->getInst() == "AND")
        regs[inst->getR1()] &= regs[inst->getR2()];
    else if(inst->getInst() == "OR")
        regs[inst->getR1()] |= regs[inst->getR2()];
	else if (inst->getInst() == "LDX")
	{
		int endFis = gerente->translate(regs[inst->getR2()], pcb);
		regs[inst->getR1()] = memoria[endFis];
	}
        
	else if (inst->getInst() == "STX")
	{
		int endFis = gerente->translate(regs[inst->getR1()], pcb);
		memoria[endFis] = regs[inst->getR2()];
	}
        
    else if(inst->getInst() == "NOT")
        regs[inst->getR1()] = !(regs[inst->getR1()]);
    else if(inst->getInst() == "SHL")
        regs[inst->getR1()] = regs[inst->getR1()]<<1;
    else if(inst->getInst() == "SHR")
        regs[inst->getR1()] = regs[inst->getR1()]>>1;
    else if(inst->getInst() == "SWAP")
    {
        regs[7] = regs[3];
        regs[6] = regs[2];
        regs[5] = regs[1];
        regs[4] = regs[0];
    }
	else if (inst->getInst() == "STOP")
	{
	}
	else if (inst->getInst() == "TRAP")
	{
		if (regs[inst->getR1()] == 1)
		{
			*interruptFlag = 1;
			int endFis = gerente->translate(regs[inst->getR2()], pcb);
			*interruptParameter = endFis;
		}
		else if (regs[inst->getR1()] == 2)
		{
			*interruptFlag = 2;
			int endFis = gerente->translate(regs[inst->getR2()], pcb);
			*interruptParameter = memoria[endFis];
		}
	}
    else
        cout << "invalid instruction" << endl;
}
