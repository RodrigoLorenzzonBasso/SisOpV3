#include "ProcessControl.h"

ProcessControl::ProcessControl(unsigned int* memoria, int tamPart)
{
	readyQueue = new queue<ProcessControlBlock*>;
	pcbList = new vector<ProcessControlBlock*>;
	memoryManager = new MemControl(memoria, tamPart);
	blockedQueue = new vector<ProcessControlBlock*>;
	requestQueue = new queue<Request*>;
	timer = new Timer();
	nProcessos = 0;
	interrupted = false;
	timeSliceMS = 0.5;
	this->tamPart = tamPart;
}

ProcessControl::~ProcessControl()
{
	delete readyQueue;
	delete pcbList;
	delete memoryManager;
	delete timer;
}

ProcessControlBlock* ProcessControl::createProcess(Program* p)
{
	int indexParticao = memoryManager->alocarParticao();
	if (indexParticao == -1)
		return nullptr;

	if (*debug == true)
	{
		cout << "Partition " << indexParticao << " allocated" << endl;
	}

	memoryManager->carga(p, indexParticao);

	int base = indexParticao * tamPart;
	int limit = ((indexParticao + 1) * tamPart) - 1;

	nProcessos++;
	ProcessControlBlock* pcb = new ProcessControlBlock(indexParticao,base,limit);
	pcbList->push_back(pcb);

	rdyQueue.lock();
	readyQueue->push(pcb);
	rdyQueue.unlock();

	return pcb;

}

int ProcessControl::deleteProcess(ProcessControlBlock* pcb)
{
	for (auto it = pcbList->begin(); it != pcbList->end(); it++)
	{
		if (*it == pcb)
		{
			int particao = (*it)->getParticao();
			memoryManager->desalocarParticao(particao);
			
			cout << "Partition " << particao << " deallocated" << endl;

			
			pcbList->erase(it);
			if (pcb == pcbRodando)
			{
				pcbRodando = nullptr;
			}
			nProcessos--;
			return 0;
		}
	}
	cout << "Esse Processo nao estava na lista de processos criados" << endl;
	return -1;
}

void ProcessControl::saveContext(ProcessControlBlock* pcb)
{
	rdyQueue.lock();
	readyQueue->push(pcb);
	rdyQueue.unlock();
}

void ProcessControl::restoreContext(ProcessControlBlock* pcb)
{
}

void ProcessControl::timerControl()
{
	rdyQueue.lock();
	if (readyQueue->empty() == false)
	{
		ProcessControlBlock* pcb = readyQueue->front();
		rdyQueue.unlock();

		if (pcb != pcbRodando && pcb != nullptr)
		{
			rdyQueue.lock();
			readyQueue->pop();
			rdyQueue.unlock();
			if (pcbRodando != nullptr)
			{
				saveContext(pcbRodando);
			}
			restoreContext(pcb);
			pcbRodando = pcb;
		}
	}
	else
	{
		rdyQueue.unlock();
	}
	interrupted = false;

}

ProcessControlBlock* ProcessControl::getPcbRodando()
{
	return pcbRodando;
}

bool ProcessControl::isInterrupted()
{
	return interrupted;
}

MemControl* ProcessControl::getMemoryManager()
{
	return memoryManager;
}

void ProcessControl::THREAD_TIMER(bool * debug, bool * stop)
{
	this->debug = debug;
	this->stop = stop;

	timer->setReset(false);
	timer->resetTimer();
	while (true)
	{
		if (*stop == true)
			break;

		if (interrupted == false)
		{
			double time = timer->timeMillis();
			if (time >= timeSliceMS)
			{
				interrupted = true;
				timer->resetTimer();
			}
		}

	}
}

void ProcessControl::mudaPcbRodando(ProcessControlBlock *newPcb)
{
	pcbRodando = newPcb;
}
