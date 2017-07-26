#include "WorkQueue.h"

#include <queue>

WorkQueue* WorkQueue::instance = 0;

WorkQueue* WorkQueue::getInstance()
{
  if(instance==0) instance = new WorkQueue();
  return instance;
}

void WorkQueue::add(Device *d)
{
	this->queue.push(d);
}
void WorkQueue::remove(Device *d)
{
	this->toDelete.push_back(d);
}
void WorkQueue::doWork()
{
	if(queue.size()>0)
	{
		Device *first = queue.front();
		
		int size = toDelete.size();
		toDelete.remove(first);
		if(size==toDelete.size())
		{
			bool retainInQueue = first->doWork();
			queue.pop();
			if(retainInQueue)queue.push(first);
		}
		else
		{
			queue.pop();
		}
	}
}