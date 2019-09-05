/// Rodrigo Basso
/// Rodrigo Perozzo

/*
	Shell
*/

#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <vector>

using namespace std;

#include "Assembler.h"
#include "Program.h"
#include "ProcessControl.h"
#include "ProcessControlBlock.h"
#include "CPU.h"
#include <queue>

//macros para utiliza��o dos bits de maneira mais facil
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= (~(1<<bit)))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit) (valor & (1<<bit))
//

//defini�oes de constantes do programa
#define TAM_MEM 1024
#define TAM_PART 16
//

class Shell
{
public:
    Shell(unsigned int * memoria);
	void THREAD_SHELL(ProcessControl * processManager, bool * debug, bool * stop);

	queue<int>* buffer = nullptr;

private:
	void printBit(unsigned int val);
	void printMem();

	unsigned int* memoria = nullptr;
	bool* debug = nullptr;
	bool* stop = nullptr;
};

#endif