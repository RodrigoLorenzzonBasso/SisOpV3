/// Rodrigo Basso
/// Rodrigo Perozzo

#include "Program.h"

Program::Program(vector<int>* prog)
{
	this->prog = prog;
	//cout << "Program: " << this->prog->front() << endl;
	nFrames = this->prog->front();
	this->prog->erase(this->prog->begin());
}

Program::~Program()
{
	delete prog;
}
