#include <chrono>
#include <queue>
#include <string>
#include <fstream>
#include "fcfs.h"
#include "PCBObject.h"

FCFS::FCFS(PCBObject pcb) {
    ready.push(pcb);
}

FCFS::FCFS(queue<PCBObject> ready) {
    this->ready = ready;
}

void FCFS::addReady(PCBObject pcb, int curTime) {
    pcb.setArrivalTime(curTime);
    ready.push(pcb);
}

void FCFS::removeReady(int curTime) {
    ready.front().setDepartureTime(curTime);
    ready.pop();
}

PCBObject FCFS::checkTop() {
    return ready.front();
}

int FCFS::run(int curTime) {
    PCBObject pcb = ready.front();
    ready.pop();
    pcb.setResponseTime(curTime);
    pcb.setWaitTime(curTime);
    pcb.setAccumulatedTime(pcb.getExecutionTime());
    curTime += pcb.getExecutionTime();
    // print pcb object
    return curTime;
}

void FCFS::csv(PCBObject pcb) {
    ofstream csvFile("data.csv");
    csvFile << pcb.getPID() << "," << pcb.getResponseTime() << "," << pcb.getWaitTime() << "," << pcb.getAccumulatedTime() << "," << endl;
    csvFile.close();
}
