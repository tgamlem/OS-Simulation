#ifndef FCFS_H
#define FCFS_H
#include <string>
#include <queue>
#include <vector>
#include "PCBObject.h"
#include <mutex>

class FCFS {
    private:
        queue<PCBObject> ready;
        int cpus;
        mutex m;
    public:
        // constructor with an empty ready queue.
        FCFS();
        // constructor with one object
        FCFS(PCBObject pcb);
        // constructor with a queue of objects
        FCFS(queue<PCBObject> ready);
        // check top of ready queue
        PCBObject checkTop();
        // check if ready queue is empty
        bool isEmpty();
        // add an object to the ready queue
        void addReady(PCBObject pcb, int curTime);
        // remove an object from the ready queue
        void removeReady(int curTime);
        // run a process
        void run(string fileName, int& curTime);

        int getCPUCount();
        void setCPUCount(int cpuCount);
        // write pcb data to csv file
        void csv(string fileName, PCBObject pcb);
};

#endif