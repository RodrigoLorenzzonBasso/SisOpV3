/// Rodrigo Basso
/// Rodrigo Perozzo

/*
	Abstracao de dados para representacao de um programa
	na forma de um vetor(prog) de codigos fontes de instrucoes
*/

#ifndef PROGRAM_H
#define PROGRAM_H

#include "MicroInstruction.h"
#include <vector>
#include <iostream>

using namespace std;

class Program
{
public:
	Program(vector<int>* prog);
	~Program();
	vector<int>* prog = nullptr;
	int nFrames;
};

#endif