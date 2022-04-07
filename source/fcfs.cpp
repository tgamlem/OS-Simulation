#include <chrono>
#include <queue>
#include <string>
#include <fstream>
#include "fcfs.h"
#include "PCBObject.h"
#include <mutex>

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

int FCFS::run(string fileName, int curTime) {
    //CPUS run in strict parallel!
        m.lock();
        PCBObject pcb = ready.front();
        ready.pop();
        pcb.setResponseTime(curTime);
        pcb.setWaitTime(curTime);
        pcb.setAccumulatedTime(pcb.getExecutionTime());
        curTime += pcb.getExecutionTime();
        csv(fileName, pcb);
        m.unlock();
        return curTime;
}

int FCFS::getCPUCount() {
    return cpus;
}

void FCFS::setCPUCount(int cpuCount) {
    cpus = cpuCount;
}

void FCFS::csv(string fileName, PCBObject pcb) {
    ofstream csvFile(fileName, fstream::app);
    csvFile << pcb.getPID() << "," << pcb.getResponseTime() << "," << pcb.getWaitTime() << "," << pcb.getAccumulatedTime() << "," << endl;
    csvFile.close();
}
