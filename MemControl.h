/*
	Gerente de Mem�ria

	abstra��o utilizada pelo gerente de processos para gerenciar a memoria;
	implementa os m�todos de alocar/desalocar particao e carga de um programa;
*/

#ifndef MEMCONTROL_H
#define MEMCONTROL_H

#include "MicroInstruction.h"
#include "Program.h"
#include <vector>
#include <iostream>

using namespace std;

class MemControl
{
public:
	MemControl(unsigned int * memoria, int tamPart);
	~MemControl();
	void carga(Program * p, int indexParticao);
	int alocarParticao();
	int desalocarParticao(int particao);
	int translate(int endLogico, int index);

	unsigned int * memoria = nullptr;

private:
	
	int tamPart;
	int nPart;
	vector<bool> busy;

	

};

#endif