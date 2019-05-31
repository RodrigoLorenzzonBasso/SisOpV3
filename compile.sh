#!/bin/bash
g++ -std=c++11 IO.cpp main.cpp Assembler.cpp CPU.cpp Execution.cpp MemControl.cpp MicroInstruction.cpp ProcessControlBlock.cpp Program.cpp Request.cpp Shell.cpp StateCpu.cpp Timer.cpp ProcessControl.cpp -o MV -pthread
