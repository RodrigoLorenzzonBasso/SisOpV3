#include "MemControl.h"




MemControl::MemControl(unsigned int * memoria, int tamPart)
{
	this->memoria = memoria;
	this->tamPart = tamPart;
	
	this->nPart = 1024 / (tamPart - 1);

	for (int i = 0; i < nPart; i++)
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

	if (int(prog->size()) >= tamPart)
	{
		cout << "Tamanho de programa nao suportado" << endl;
		return;
	}


	int base = indexParticao * tamPart;

	vector<int>::iterator it = prog->begin();
	int i = base;
	while (it != prog->end())
	{
		memoria[i] = *it;
		it++;
		i++;
	}
}

int MemControl::alocarParticao()
{
	for (int i = 0; i < nPart; i++)
	{
		if (busy[i] == false)
		{
			busy[i] = true;
			return i;
		}
	}
	cout << "Nao foi possivel alocar particao" << endl;
	return -1;
}

int MemControl::desalocarParticao(int particao)
{
	if (busy[particao] == true)
	{
		busy[particao] = false;
		return 0;
	}


	cout << "Nao foi possivel desalocar particao" << endl;		
	return -1;
}

int MemControl::translate(int endLogico, int index)
{
	int endFisico;
	int base = index * tamPart;
	int limit = ((index + 1) * tamPart) - 1;

	endFisico = endLogico + (index * tamPart);

	if(endFisico >= base || endFisico <= limit)
		return endFisico;
	else
	{
		cout << "Enderecamento indevido" << endl;
		return -1;
	}
		
}