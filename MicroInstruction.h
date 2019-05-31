/*
	Abstração de dados que representa 1(uma) instrução

	os bits da instrução sao recebidos na forma de codigo objeto e 
	separados de forma mais visivel em atributos da classe;
*/

#ifndef MICROINSTRUCTION_H
#define MICROINSTRUCTION_H

#include <iostream>

using namespace std;

class MicroInstruction
{
    public:
        MicroInstruction(int instCode, int address, int tamPart);
        string getInst();
		int getInstCode();
		int getAddress();
        int getImm();
        int getR1();
        int getR2();
		int getIndex();

		void setInstCode(int instCode);
		void reDecode();

    private:
        string inst;
		int instCode;
        int imm;
        int r1;
        int r2;
		int address;
		int index;

        void decode(int instCode);
        int bitExtracted(int val, int k, int p);
};

#endif // MICROINSTRUCTION_H
