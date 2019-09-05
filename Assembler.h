/// Rodrigo Basso
/// Rodrigo Perozzo

/*
	Classe montadora de c�digo objeto

	l� arquivo .txt com instru��es e retorna c�digo objeto em forma de vector<int>;
*/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#define testBit(valor,bit) (valor & (1<<bit))

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Assembler
{
    public:
        Assembler();
        vector<int> * generateSource(string filename);
    private:
        vector<string> * readFile(string filename);
        unsigned int decodeInst(string i);
        unsigned int decodeOp(string op, string i);
        unsigned int decodeOp2(string op, string i);
        int bitExtracted(int val, int k, int p);

};

#endif // ASSEMBLER_H
