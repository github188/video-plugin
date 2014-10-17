#include "stdafx.h"
#include "BuffQueue.h"
BuffQueue::BuffQueue()
{
	InitializeCriticalSection(&CS);
}
BuffQueue::~BuffQueue(){
	DeleteCriticalSection( & CS);
}
bool BuffQueue::getdatanum(){
	EnterCriticalSection( &CS);
	bool re=buffqueue.empty();
	LeaveCriticalSection( &CS);
	return re;
}

package BuffQueue::popdata(){
	
	EnterCriticalSection( &CS);	
	package pkg=buffqueue.front();
	buffqueue.pop();
	LeaveCriticalSection( &CS);
	return pkg;
}

void BuffQueue::pushdata(package pkg){

	EnterCriticalSection( &CS);
	buffqueue.push(pkg);
	LeaveCriticalSection( &CS);

}

void BuffQueue::popall()
{
	EnterCriticalSection( &CS);
	while(buffqueue.size()>0)
		buffqueue.pop();
	LeaveCriticalSection( &CS);
}

int BuffQueue:: num ()
{
	return buffqueue.size();
}