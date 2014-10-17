#ifndef _BUFFQUEUE_H
#define _BUFFQUEUE_H
#include <windows.h>
#include <queue>

class package
{
public:
	 char buff[1500];
	 int buffsize;
};

class BuffQueue{
private:
	std::queue<package> buffqueue;
	CRITICAL_SECTION CS;
public:
	BuffQueue();
	void pushdata(package pkg);
	package popdata();
	bool getdatanum();
	void popall();
	int num ();
	~BuffQueue();
};
#endif