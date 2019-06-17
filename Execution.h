/// Rodrigo Basso
/// Rodrigo Perozzo

/*
	Classe que implementa a execu��o das instru�oes

	apenas 1 m�todo importante, execute, que, recebe uma microinstru�ao
	e executa a opera��o contida nela;
*/

#ifndef EXECUTION_H
#define EXECUTION_H

#include "MicroInstruction.h"
#include <iostream>
#include "MemControl.h"
#include "ProcessControlBlock.h"

using namespace std;


class Execution
{
    public:
        Execution(unsigned int * memoria, MemControl * gerente);
        void execute(MicroInstruction * inst, int * pc, int * regs, int *interruptFlag, int *interruptParameter, ProcessControlBlock * pcb);

    private:
        unsigned int * memoria = nullptr;
		MemControl * gerente = nullptr;

};

#endif // EXECUTION_H
