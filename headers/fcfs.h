#ifndef FCFS_H
#define FCFS_H
#include <string>
#include <queue>
#include "PCBObject.h"

class FCFS {
    private:
        queue<PCBObject> ready;
    public:
        // constructor with one object
        FCFS(PCBObject pcb);
        // constructor with a queue of objects
        FCFS(queue<PCBObject> ready);
        // add an object to the ready queue
        void addReady(PCBObject pcb, int curTime);
        // remove an object from the ready queue
        void removeReady(int curTime);
        // run a process
        int run(int curTime);
};

#endif