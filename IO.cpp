/// Rodrigo Basso
/// Rodrigo Perozzo

#include "IO.h"

IO::IO()
{

}

void IO::THREAD_IO(ProcessControl* processManager, bool* debug, bool* stop, queue<int>* buffer)
{
    while(!(*stop))
    {
        // REQUEST
		reqQueue.lock();
		if (!processManager->requestQueue->empty())
		{
			Request* temp = processManager->requestQueue->front();
			reqQueue.unlock();
			if (temp->flag == 1)
			{
				if(!buffer->empty())
				{
					reqQueue.lock();
					processManager->requestQueue->pop();
					reqQueue.unlock();
					int val = buffer->front();

					unsigned int val_u = 0;

					if(val >= 0)
					{
						val_u = (unsigned int)val;
					}
					else
					{

					}

					buffer->pop();
					unsigned int * mem_pointer = processManager->getMemoryManager()->memoria;	
					mem_pointer[temp->param] = val_u;
					//
					cout << "Foi colocado: " << val_u << " na posicao de memoria: " << temp->param << endl;
					//
					bckQueue.lock();
					for (auto it = processManager->blockedQueue->begin(); it != processManager->blockedQueue->end(); it++)
					{
						if ((*it)->thisId == temp->id)
						{
							ProcessControlBlock * temporario = (*it);
							ProcessControlBlock * novo = new ProcessControlBlock(*temporario);
							processManager->blockedQueue->erase(it);
							rdyQueue.lock();
							processManager->readyQueue->push(novo);
							rdyQueue.unlock();
							processManager->pcbList->push_back(novo);
							break;
						}
					}
					bckQueue.unlock();
				}
				else
				{
					//cout << "Request com Buffer Vazio" << endl;
				}

			}
			//Write Trap
			else if (temp->flag == 2)
			{
				reqQueue.lock();
				processManager->requestQueue->pop();
				reqQueue.unlock();
				cout << "Print: " << temp->param << endl;
				bckQueue.lock();
				for (auto it = processManager->blockedQueue->begin(); it != processManager->blockedQueue->end(); it++)
				{
					if ((*it)->thisId == temp->id)
					{
						ProcessControlBlock * temporario = (*it);
						ProcessControlBlock * novo = new ProcessControlBlock(*temporario);
						processManager->blockedQueue->erase(it);
						rdyQueue.lock();
						processManager->readyQueue->push(novo);
						rdyQueue.unlock();
						processManager->pcbList->push_back(novo);
						break;
					}
				}
				bckQueue.unlock();
			}
		}
		else
		{
			reqQueue.unlock();
			while(!buffer->empty())
			{
				buffer->pop();
			}
		}
		// END REQUEST
    }
}