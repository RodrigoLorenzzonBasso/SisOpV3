/// Rodrigo Basso
/// Rodrigo Perozzo

#include "MicroInstruction.h"
#define testBit(valor,bit) (valor & (1<<bit))
#define setBit(valor,bit) (valor |= (1<<bit))

MicroInstruction::MicroInstruction(int instCode, int address, int tamPart)
{
    inst = "";
    imm = 0;
    r1 = 0;
    r2 = 0;
	this->address = address;

	index = address / tamPart;

	this->instCode = instCode;

    decode(instCode);
}

void MicroInstruction::decode(int instCode)
{
    int opcode = 0;
    opcode = bitExtracted(instCode, 5, 27);

    if(opcode == 0) inst = "JMP";
    else if(opcode == 1) inst ="JMPI";
    else if(opcode == 2) inst ="JMPIG";
    else if(opcode == 3) inst ="JMPIL";
    else if(opcode == 4) inst ="JMPIE";
    else if(opcode == 8) inst ="ADDI";
    else if(opcode == 9) inst ="SUBI";
    else if(opcode == 10) inst ="ANDI";
    else if(opcode == 11) inst ="ORI";
    else if(opcode == 12) inst ="LDI";
    else if(opcode == 13) inst ="LDD";
    else if(opcode == 14) inst ="STD";
    else if(opcode == 16) inst ="ADD";
    else if(opcode == 17) inst ="SUB";
    else if(opcode == 28) inst ="MULT";
    else if(opcode == 18) inst ="AND";
    else if(opcode == 19) inst ="OR";
    else if(opcode == 20) inst ="LDX";
    else if(opcode == 21) inst ="STX";
    else if(opcode == 24) inst ="NOT";
    else if(opcode == 25) inst ="SHL";
    else if(opcode == 26) inst ="SHR";
    else if(opcode == 27) inst ="SWAP";
    else if(opcode == 31) inst ="STOP";
	else if (opcode == 5) inst ="TRAP";
    else inst = "invalid instruction";

    imm = bitExtracted(instCode,16,0);
    if(testBit(imm,15) != 0)
    {
        for(int i = 15; i <32; i++)
        {
            setBit(imm,i);
        }
    }

    r1 = bitExtracted(instCode,3,24);
    r2 = bitExtracted(instCode,3,21);
}

int MicroInstruction::bitExtracted(int val, int k, int p)
{
    return (((1 << k) - 1) & (val >> p));
}

int MicroInstruction::getImm()
{
    return imm;
}

int MicroInstruction::getR1()
{
    return r1;
}

int MicroInstruction::getR2()
{
    return r2;
}

int MicroInstruction::getIndex()
{
	return index;
}

void MicroInstruction::setInstCode(int instCode)
{
	this->instCode = instCode;
}

void MicroInstruction::reDecode()
{
	decode(this->instCode);
}

string MicroInstruction::getInst()
{
    return inst;
}

int MicroInstruction::getInstCode()
{
	return instCode;
}

int MicroInstruction::getAddress()
{
	return address;
}






