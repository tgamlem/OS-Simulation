#include <chrono>
#include <queue>
#include <string>
#include "fcfs.h"
#include "PCBObject.h"

FCFS::FCFS() {
    this->cpus = 1;
}


FCFS::FCFS(PCBObject pcb) {
    ready.push(pcb);
    this->cpus = 1;
}

FCFS::FCFS(queue<PCBObject> ready) {
    this->ready = ready;
    this->cpus = 1;
}

void FCFS::addReady(PCBObject pcb, int curTime) {
    if (pcb.getArrivalTime() == 0) {
        pcb.setArrivalTime(curTime);
    }
    ready.push(pcb);
}

void FCFS::removeReady(int curTime) {
    ready.front().setDepartureTime(curTime);
    ready.pop();
}

PCBObject FCFS::checkTop() {
    return ready.front();
}

bool FCFS::isEmpty() {
    return ready.empty();
}

vector<int> FCFS::run(vector<int> curTime) {
    //CPUS run in strict parallel!
    for (int i = 0; i < cpus; i++) {
        PCBObject pcb = ready.front();
        ready.pop();
        pcb.setResponseTime(curTime[i]);
        pcb.setWaitTime(curTime[i]);
        pcb.setAccumulatedTime(pcb.getExecutionTime());
        curTime[i] += pcb.getExecutionTime();
    
    }
    // print pcb object
    return curTime;
}

int FCFS::getCPUCount() {
    return cpus;
}

void FCFS::setCPUCount(int cpuCount) {
    cpus = cpuCount;
}