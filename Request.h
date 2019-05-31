#ifndef REQUEST_H
#define REQUEST_H

class Request
{
public:
	Request(int id, int flag, int param);

	int id;
	int flag;
	int param;
};


#endif