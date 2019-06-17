/// Rodrigo Basso
/// Rodrigo Perozzo

#include "Shell.h"

Shell::Shell(unsigned int * memoria)
{
	this->memoria = memoria;
	this->buffer = new queue<int>();
}

void Shell::THREAD_SHELL(ProcessControl* processManager, bool* debug, bool* stop)
{
	Assembler* as = new Assembler();
	vector<int>* fontCode = nullptr;
	this->debug = debug;
	this->stop = stop;

	cout << "type help for all commands" << endl;

	while (true)
	{
		if (*stop == true)
			break;

		cout << ">> ";
		string typed;
		getline(cin, typed);

		if (typed == "exit")
		{
			*stop = true;
		}
		else if (typed == "help")
		{
			cout << "help" << endl;
			cout << "exec [Filename]" << endl;
			cout << "print [Device] (mem)" << endl;
			cout << "debug (enable/disable debug mode)" << endl;
			if (*debug == true)
			{
				cout << "load (load all programs in the memory)" << endl;
				cout << "mem [integer] [address] (put some integer in the memory)" << endl;
			}
			cout << "exit" << endl;
		}
		else if (typed == "load")
		{
			if (*debug == true)
			{
				/*fontCode = as->generateSource("fibonacci.txt");
				Program p(fontCode);
				processManager->createProcess(&p);

				fontCode = as->generateSource("fibonacci2.txt");
				p.prog = fontCode;
				processManager->createProcess(&p);

				fontCode = as->generateSource("factorial.txt");
				p.prog = fontCode;
				processManager->createProcess(&p);

				fontCode = as->generateSource("sort.txt");
				p.prog = fontCode;
				processManager->createProcess(&p);
*/

				/*fontCode = as->generateSource("TesteTrap.txt");
				Program p(fontCode);
				//p.prog = fontCode;
				processManager->createProcess(&p); 

				fontCode = as->generateSource("TesteTrap.txt");
				p.prog = fontCode;
				processManager->createProcess(&p); 

				fontCode = as->generateSource("TesteTrap.txt");
				p.prog = fontCode;
				processManager->createProcess(&p); */

				fontCode = as->generateSource("fibonacci.txt");
				Program p0(fontCode);
				//p.prog = fontCode;
				processManager->createProcess(&p0); 

				fontCode = as->generateSource("fibonacci.txt");
				Program p1(fontCode);;
				processManager->createProcess(&p1); 

				fontCode = as->generateSource("fibonacci.txt");
				Program p2(fontCode);
				processManager->createProcess(&p2);

				cout << "all loaded" << endl;
			}
		}
		else if (typed.substr(0, 3) == "mem")
		{
			if (*debug == true)
			{

			}
		}
		else if (typed == "debug")
		{
			if (*debug == false)
			{
				*debug = true;
				cout << "debug mode enabled, type help for more options" << endl;
			}
			else
			{
				*debug = false;
				cout << "debug mode disabled" << endl;
			}
		}
		else if (typed.substr(0, 4) == "exec")
		{
			cout << "executing. . ." << endl;
			if (typed.size() <= 4)
			{

			}
			else
			{
				string filename = typed.substr(5);
				fontCode = as->generateSource(filename);
				if (fontCode == nullptr)
					cout << "unrecognized file" << endl;
			}
			
			Program p(fontCode);
			processManager->createProcess(&p);

		}
		else if (typed.substr(0, 5) == "print")
		{
			if (typed.size() <= 8)
			{

			}
			else if (typed.substr(6, 3) == "mem")
			{
				printMem();
			}
		}
		else if (typed.substr(0, 5) == "input")
		{
			if (typed.size() <= 5)
			{

			}
			else
			{
				int n = stoi(typed.substr(6));
				cout << "numero: " << n << endl;
				buffer->push(n);
			}
		}	

		//cout << buffer->front() << endl;

	}
}

void Shell::printBit(unsigned int val)
{
	cout << "bits: ";
	for (int i = 31; i >= 0; i--)
	{
		if (testBit(val, i) > 0) cout << "1";
		else cout << "0";
	}
	cout << endl;
}

void Shell::printMem()
{
	for (int i = 0; i < TAM_MEM; i++)
	{
		if (i % TAM_PART == 0)
		{
			cout << "Frame: " << i/TAM_PART << endl;
		}

		if (memoria[i] != 0)
		{
			cout << " " << i << " \t";
			printBit(memoria[i]);
		}	
	}

	cout << endl;
}
