/*
	Abstra��o de dados para representa��o de um programa
	na forma de um vetor(prog) de codigos fontes de instru�oes
*/

#ifndef PROGRAM_H
#define PROGRAM_H

#include "MicroInstruction.h"
#include <vector>

class Program
{
public:
	Program(vector<int>* prog);
	~Program();
	vector<int>* prog = nullptr;
};

#endif