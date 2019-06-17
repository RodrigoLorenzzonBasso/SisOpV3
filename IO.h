/// Rodrigo Basso
/// Rodrigo Perozzo

#ifndef IO_H
#define IO_H

#include "ProcessControl.h"
#include <queue>
#include <iostream>
#include "Request.h"
#include "Mutex.h"

using namespace std;

class IO
{
    public:
        IO();
        void THREAD_IO(ProcessControl* processManager, bool* debug, bool* stop, queue<int>* buffer);
    private:

};

#endif