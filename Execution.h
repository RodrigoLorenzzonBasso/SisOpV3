/*
	Classe que implementa a execução das instruçoes

	apenas 1 método importante, execute, que, recebe uma microinstruçao
	e executa a operação contida nela;
*/

#ifndef EXECUTION_H
#define EXECUTION_H

#include "MicroInstruction.h"
#include <iostream>
#include "MemControl.h"

using namespace std;


class Execution
{
    public:
        Execution(unsigned int * memoria, MemControl * gerente);
        void execute(MicroInstruction * inst, int * pc, int * regs, int *interruptFlag, int *interruptParameter);

    private:
        unsigned int * memoria = nullptr;
		MemControl * gerente = nullptr;

};

#endif // EXECUTION_H
