#include "CPU.h"

mutex reqQueue;
mutex rdyQueue;
mutex bckQueue;

CPU::CPU(int tamPart, unsigned int * memoria, MemControl * memoryManager)
{
	this->tamPart = tamPart;
	this->memoria = memoria;
	ex = new Execution(memoria, memoryManager);
	interruptFlag = 0;
}

void CPU::setSt(StateCpu* st)
{
	this->st = st;
}

MicroInstruction* CPU::fetch()
{
	unsigned int temp = memoria[*st->getPc() + *st->getBase()];
	MicroInstruction* microins = new MicroInstruction(temp, *st->getPc() + *st->getBase(), tamPart);
	return microins;
}

void CPU::incPc()
{
	st->incPc();
}

int CPU::execInst(int *interruptParam)
{
	MicroInstruction* temp = fetch();
	int * pc = st->getPc();
	interruptFlag = 0;

	if (*debug == true)
	{
		cout << "-------------------------" << endl;
		cout << "Instruction: " << temp->getInst() << endl;
		cout << "Partition: " << temp->getIndex() << endl;
		cout << "-------------------------" << endl;
	}

	if (temp->getInst() == "STOP")
	{
		delete temp;
		return -1;
	}

	ex->execute(temp, pc, st->getRegs(), &interruptFlag, interruptParam);

	incPc();

	if (temp->getInst() == "TRAP")
	{
		delete temp;
		return interruptFlag;
	}

	delete temp;
	return 0;
}

void CPU::THREAD_CPU(ProcessControl * processManager, bool * debug, bool * stop, queue<int> * buffer)
{
	this->debug = debug;
	this->stop = stop;

	int interruptParam = 0;

	while(true)
	{ 
		if (*stop == true)
			break;

		if (processManager->isInterrupted())
		{
			processManager->timerControl();
			//if (processManager->getPcbRodando() != nullptr)
			//	cout << "==" << endl << "SCHEDULING BY TIMESLICE" << endl << "==" << endl;
			if (processManager->getPcbRodando() != nullptr)
			{
				st = processManager->getPcbRodando()->getSt();
			}
		}
		if (processManager->getPcbRodando() != nullptr)
		{

			//EXEC INSTRUCTION
			int i = execInst(&interruptParam); //retorna 0 por padrao
			////////////////

			//Read Trap
			if (i == 1)
			{
				cout << "Interrupcao de Leitura" << endl << endl;
				Request * r1 = new Request(processManager->getPcbRodando()->thisId, i, interruptParam);
				reqQueue.lock();
				processManager->requestQueue->push(r1);
				reqQueue.unlock();
				bckQueue.lock();
				processManager->blockedQueue->push_back(processManager->getPcbRodando());
				bckQueue.unlock();
				rdyQueue.lock();
				if (!processManager->readyQueue->empty())
				{
					ProcessControlBlock * tempp = processManager->readyQueue->front();
					processManager->readyQueue->pop();
					rdyQueue.unlock();
					processManager->mudaPcbRodando(tempp);
					st = processManager->getPcbRodando()->getSt();
				}
				else
				{
					rdyQueue.unlock();
					processManager->mudaPcbRodando(nullptr);
				}
			}
			//Write Trap
			else if (i == 2)
			{
				cout << "Interrupcao de Escrita na tela" << endl << endl;
				Request * r1 = new Request(processManager->getPcbRodando()->thisId, i, interruptParam);
				reqQueue.lock();
				processManager->requestQueue->push(r1);
				reqQueue.unlock();
				bckQueue.lock();
				processManager->blockedQueue->push_back(processManager->getPcbRodando());
				bckQueue.unlock();
				rdyQueue.lock();
				if (!processManager->readyQueue->empty())
				{
					ProcessControlBlock * tempp = processManager->readyQueue->front();
					processManager->readyQueue->pop();
					rdyQueue.unlock();
					processManager->mudaPcbRodando(tempp);
					st = processManager->getPcbRodando()->getSt();
				}
				else
				{
					rdyQueue.unlock();
					processManager->mudaPcbRodando(nullptr);
				}
			//Stop
			}
			else if (i == -1)
			{
				processManager->deleteProcess(processManager->getPcbRodando());
			}
		}
	}
}


