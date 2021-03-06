/// Rodrigo Basso
/// Rodrigo Perozzo

/*
	Gerente de Memoria

	abstracao utilizada pelo gerente de processos para gerenciar a memoria;
	implementa os metodos de alocar/desalocar paginas e frames respectivos e da carga de um programa;
*/

#ifndef MEMCONTROL_H
#define MEMCONTROL_H

#include "MicroInstruction.h"
#include "Program.h"
#include <vector>
#include <iostream>
#include "ProcessControlBlock.h"

using namespace std;

class MemControl
{
public:
	MemControl(unsigned int * memoria, int tamPart);
	~MemControl();
	void carga(Program * p, int indexParticao);
	int alocarParticao(int n);
	int desalocarParticao(int particao, ProcessControlBlock * pcb);
	int translate(int endLogico, ProcessControlBlock * pcb);

	unsigned int * memoria = nullptr;

private:
	
	int tamFrame;
	int nFrames;
	vector<bool> busy;

	

};

#endif