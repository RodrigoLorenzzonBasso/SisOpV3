#include "Program.h"

Program::Program(vector<int>* prog)
{
	this->prog = prog;
}

Program::~Program()
{
	delete prog;
}
