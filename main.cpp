 /**
Nomes:  Rodrigo Basso e Rodrigo Perozzo
Status: Completo

Trabalho Parcial 2 de Sistemas Operacionais
	Maquina Virtual com gerente de memoria, gerente de processos,
	escalonagem de processos e execu��o paralela
**/


#include <iostream>
#include <thread>
#include <queue>
#include "ProcessControl.h"
#include "CPU.h"
#include "Shell.h"
#include "IO.h"

using namespace std;

//definicoes de constantes do programa
#define TAM_MEM 1024
#define TAM_PART 16
//

void callThreadTimer(ProcessControl* manager, bool* debug, bool* stop);
void callThreadCPU(CPU* cpu, ProcessControl* manager, bool* debug, bool* stop, queue<int>* buffer);
void callThreadShell(Shell* shell, ProcessControl* manager, bool* debug, bool* stop);
void callThreadIO(ProcessControl* manager, bool* debug, bool* stop, queue<int>* buffer, IO* io);

int main()
{

	unsigned int memoria[TAM_MEM];

	for (int i = 0; i < TAM_MEM; i++)
	{
		memoria[i] = 0;
	}

	bool debug = false;
	bool stop = false;



	ProcessControl* processManager = new ProcessControl(memoria, TAM_PART);
	CPU* cpu = new CPU(TAM_PART, memoria, processManager->getMemoryManager());
	Shell* shell = new Shell(memoria);
	IO* io = new IO();

	queue<int> * buffer = shell->buffer;

	thread t1(callThreadTimer,processManager, &debug, &stop);
	thread t2(callThreadCPU, cpu, processManager, &debug, &stop, buffer);
	thread t3(callThreadShell, shell, processManager , &debug, &stop);
	thread t4(callThreadIO, processManager, &debug, &stop, buffer, io);

	if (t4.joinable())
		t4.join();
	if (t3.joinable())
		t3.join();
	if (t2.joinable())
		t2.join();
	if (t1.joinable())
		t1.join();


	delete processManager;
	delete cpu;
	delete shell;
	delete io;
 
    return 0;
}

void callThreadTimer(ProcessControl* manager, bool* debug, bool* stop)
{
	manager->THREAD_TIMER(debug, stop);
}

void callThreadCPU(CPU* cpu, ProcessControl* manager, bool* debug, bool* stop, queue<int> * buffer)
{
	cpu->THREAD_CPU(manager, debug, stop, buffer);
}

void callThreadShell(Shell* shell, ProcessControl* manager, bool* debug, bool* stop)
{
	shell->THREAD_SHELL(manager, debug, stop);
}

void callThreadIO(ProcessControl* manager, bool* debug, bool* stop, queue<int>* buffer, IO* io)
{
	io->THREAD_IO(manager, debug, stop, buffer);
}









