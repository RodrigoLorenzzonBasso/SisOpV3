#include "Assembler.h"

void printBitToBit(unsigned int val)
{
    cout << "bits: ";
    for(int i = 31; i >= 0; i--)
    {
        if(testBit(val,i) > 0) cout << "1";
        else cout << "0";
    }
    cout << endl;
}

Assembler::Assembler()
{

}

vector<int> * Assembler::generateSource(string filename)
/// gera codigo fonte, vindo de arquivo com instru��es
/// faz o processo de decodifica��o de divis�o dos par�metros
{
    vector<string> * font = this->readFile(filename);

	if (font == nullptr)
		return nullptr;

    vector<int> * o = new vector<int>;

    for(vector<string>::iterator i = font->begin(); i != font->end(); i++)
    {
        unsigned int opcode = 0;
        unsigned int firstOpCode = 0;
        unsigned int secondOpCode = 0;

        int pos = i->find(" ");
        string instruction = i->substr(0,pos);
        opcode = this->decodeInst(instruction);

        if(instruction != "STOP")
        {
            int pos2 = i->find(",");
            if(pos2 != -1)
            {
                string firstOp = i->substr(pos+1,pos2-pos-1);
                firstOpCode = this->decodeOp(firstOp, instruction);

                string secondOp = i->substr(pos2+1);
                secondOpCode = this->decodeOp2(secondOp,instruction);
            }
            else
            {
                string firstOp = i->substr(pos+1);
                firstOpCode = this->decodeOp(firstOp,instruction);
            }
        }

        int objectCode = 0;

        if(instruction == "JMP")
        {
            objectCode = bitExtracted(firstOpCode,16,0) | opcode | secondOpCode;
        }
        else if(instruction == "LDI" || instruction == "ADDI" || instruction == "SUBI" || instruction == "ANDI" || instruction == "ORI" || instruction == "LDD")
        {
            objectCode = firstOpCode | opcode | bitExtracted(secondOpCode,16,0);
        }
        else
        {
            objectCode = firstOpCode | opcode | secondOpCode;
        }

        o->push_back(objectCode);
    }

    delete font;
    return o;
}

vector<string> * Assembler::readFile(string filename)
{
    fstream fs;
    string line;

    vector<string> *font = new vector<string>;

    fs.open(filename.c_str(), fstream::in);

	if (fs.is_open())
	{
		while (getline(fs, line))
		{
			font->push_back(line);
		}

		fs.close();

		return font;
	}
	else
	{
		cout << "Error opening file!!!" << endl;
		return nullptr;
	}

}

unsigned int Assembler::decodeInst(string i)
{
    if(i == "JMP") return (0<<27);
    else if(i == "JMPI") return (1<<27);
    else if(i == "JMPIG") return (2<<27);
    else if(i == "JMPIL") return (3<<27);
    else if(i == "JMPIE") return (4<<27);
    else if(i == "ADDI") return (8<<27);
    else if(i == "SUBI") return (9<<27);
    else if(i == "ANDI") return (10<<27);
    else if(i == "ORI") return (11<<27);
    else if(i == "LDI") return (12<<27);
    else if(i == "LDD") return (13<<27);
    else if(i == "STD") return (14<<27);
    else if(i == "ADD") return (16<<27);
    else if(i == "SUB") return (17<<27);
    else if(i == "MULT") return (28<<27);
    else if(i == "AND") return (18<<27);
    else if(i == "OR") return (19<<27);
    else if(i == "LDX") return (20<<27);
    else if(i == "STX") return (21<<27);
    else if(i == "NOT") return (24<<27);
    else if(i == "SHL") return (25<<27);
    else if(i == "SHR") return (26<<27);
    else if(i == "SWAP") return (27<<27);
    else if(i == "STOP") return (31<<27);
	else if (i == "TRAP") return (5 << 27);
    else return (31<<27);
}

unsigned int Assembler::decodeOp(string op, string i)
{
    if(i == "LDI" || i == "ADDI" || i == "SUBI" || i == "ANDI" || i == "ORI" || i == "LDI" || i == "LDD" ||
            i == "ADD" || i == "SUB" || i == "MULT" || i == "AND" || i == "OR" || i == "LDX" || i == "STX" ||
            i == "NOT" || i == "SHL" || i == "SHR" || i == "SWAP" || i == "NOT" || i == "SHL" || i == "SHR" || i == "SWAP" ||
            i == "JMPI" || i == "JMPIG" || i == "JMPIL" || i == "JMPIE" || i == "TRAP")
    {
        op.erase(0,1); /// remove o '$'
        unsigned int opNum = 0;
        stringstream ss(op);
        ss >> opNum;
        return (opNum<<24);
    }
    else if(i == "STD" || i == "JMP")
    {
        unsigned int opNum = 0;
        stringstream ss(op);
        ss >> opNum;
        return opNum;
    }
    return 0;
}

unsigned int Assembler::decodeOp2(string op, string i)
{
    unsigned int opNum = 0;
    stringstream ss;

    if(i == "LDI" || i == "ADDI" || i == "SUBI" || i == "ANDI" || i == "ORI" || i == "LDD")
    {
        ss << op;
        ss >> opNum;
        return opNum;
    }
    else if(i == "STD")
    {
        op.erase(0,1);
        ss << op;
        ss >> opNum;
        return (opNum<<24);
    }
    else if(i == "ADD" || i == "SUB" || i == "MULT" || i == "AND" || i == "OR" || i == "LDX" || i == "STX" ||
            i == "JMPI" || i == "JMPIG" || i == "JMPIL" || i == "JMPIE" || i == "TRAP")
    {
        op.erase(0,1);
        ss << op;
        ss >> opNum;
        return (opNum<<21);
    }
    else
    {
        return 0;
    }
}

int Assembler::bitExtracted(int val, int k, int p)
{
    return (((1 << k) - 1) & (val >> p));
}

















