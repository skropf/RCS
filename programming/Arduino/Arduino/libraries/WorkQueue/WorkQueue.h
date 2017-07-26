#ifndef WorkQueue_h
#define WorkQueue_h

#include <iterator>
#include <list> 
#include <queue>
#include <Device.h>

class WorkQueue
{
  public:
    static WorkQueue * getInstance();
    void add(Device*);
    void remove(Device*);
    void doWork();
  private:
  	WorkQueue(){};
  	static WorkQueue *instance;
  	std::queue<Device*> queue;
  	std::list<Device*> toDelete;
};

#endif