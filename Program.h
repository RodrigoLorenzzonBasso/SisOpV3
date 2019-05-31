/*
	Abstração de dados para representação de um programa
	na forma de um vetor(prog) de codigos fontes de instruçoes
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