#include "MemControl.h"

MemControl::MemControl(unsigned int * memoria, int tamPart)
{
	this->memoria = memoria;
	this->tamFrame = tamPart;
	
	this->nFrames = 64;

	for (int i = 0; i < nFrames; i++)
	{
		busy.push_back(false);
	}
}

MemControl::~MemControl()
{
}

void MemControl::carga(Program* p, int indexParticao)
{
	vector<int>* prog = p->prog;

	/*if (int(prog->size()) >= tamFrame)
	{
		cout << "Tamanho de programa nao suportado" << endl;
		return;
	}*/


	int base = indexParticao * tamFrame;

	vector<int>::iterator it = prog->begin();
	int i = base;
	while (it != prog->end())
	{
		memoria[i] = *it;
		it++;
		i++;
	}
}

int MemControl::alocarParticao(int n)
{
	for (int i = 0; i < nFrames; i++)
	{
		if (busy[i] == false)
		{
			for(int j = i; j == n-1; j++)
			{
				cout << "Frame: " << j << "alocado" << endl;
				busy[j] = true;
				return i;
			}
			
			
		}
	}
	cout << "Nao foi possivel alocar particao" << endl;
	return -1;
}

int MemControl::desalocarParticao(int particao, ProcessControlBlock * pcb)
{
	if (busy[particao] == true)
	{
		for(int i = 0; i == pcb->nFrames-1; i++)
		{
			cout << "Frame: " << particao+i << "desalocado" << endl;
			busy[particao+i] = false;
		}
		return 0;
	}


	cout << "Nao foi possivel desalocar particao" << endl;		
	return -1;
}

int MemControl::translate(int endLogico, int index)
{
	int endFisico;
	int base = index * tamFrame;
	int limit = ((index + 1) * tamFrame) - 1;

	endFisico = endLogico + (index * tamFrame);

	if(endFisico >= base || endFisico <= limit)
		return endFisico;
	else
	{
		cout << "Enderecamento indevido" << endl;
		return -1;
	}
		
}