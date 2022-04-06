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

vector<int> RoundRobin::run(vector<int> curTime) {
    for (int i = 0; i < getCPUCount(); i++) {
        PCBObject pcb = checkTop();
        removeReady(curTime[i]);
        if (pcb.getResponseTime() == 0) {
            pcb.setResponseTime(curTime[i]);
        }
        pcb.setWaitTime(curTime[i]);
        if (pcb.getExecutionTime() > timeSlice) {
            int partialExecutionTime = pcb.getExecutionTime() - timeSlice;
            pcb.setAccumulatedTime(pcb.getExecutionTime());
            pcb.setExecutionTime(partialExecutionTime);
            curTime[i] += timeSlice;
            cout << pcb.getPID() << endl;
            addReady(pcb, curTime[i]);
        } else {
            pcb.setAccumulatedTime(pcb.getExecutionTime());
            curTime[i] += pcb.getExecutionTime();
        }
    }

    return curTime;
}

int RoundRobin::getTimeSlice() {
    return timeSlice;
}

void RoundRobin::setTimeSlice(int time) {
    timeSlice = time;
}

