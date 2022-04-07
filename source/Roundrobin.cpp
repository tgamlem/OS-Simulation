#include <string>
#include <iostream>
#include "PCBObject.h"
#include <fstream>
#include <list>
#include <iterator>
#include <typeinfo>
#include "DataFile.h"
#include <queue>
#include "Roundrobin.h"

RoundRobin::RoundRobin(PCBObject pcb, int timeSlice): FCFS(pcb) {
    this->timeSlice = timeSlice;
}

RoundRobin::RoundRobin() {
    this->timeSlice = 5;
}

RoundRobin::RoundRobin(queue<PCBObject> ready, int timeSlice): FCFS(ready) {
    this->timeSlice = timeSlice;
}

RoundRobin::RoundRobin(int timeSlice) : FCFS() {
    this->timeSlice = timeSlice;
}

int RoundRobin::run(string fileName, int& curTime) {
    
        PCBObject pcb = checkTop();
        removeReady(curTime);
        if (pcb.getResponseTime() == 0) {
            pcb.setResponseTime(curTime);
        }
        pcb.setWaitTime(curTime);
        if (pcb.getExecutionTime() > timeSlice) {
            int partialExecutionTime = pcb.getExecutionTime() - timeSlice;
            pcb.setAccumulatedTime(pcb.getExecutionTime());
            pcb.setExecutionTime(partialExecutionTime);
            curTime += timeSlice;
            cout << pcb.getPID() << endl;
            addReady(pcb, curTime);
        } else {
            pcb.setAccumulatedTime(pcb.getExecutionTime());
            curTime += pcb.getExecutionTime();
        }
        csv(fileName, pcb);
    

    return curTime;
}

int RoundRobin::getTimeSlice() {
    return timeSlice;
}

void RoundRobin::setTimeSlice(int time) {
    timeSlice = time;
}

