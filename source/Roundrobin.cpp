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

void RoundRobin::run(string fileName, int& curTime, mutex& m) {
    while (true) {
        if (m.try_lock() && !isEmpty()) {
            PCBObject pcb = checkTop();
            removeReady(curTime);
            m.unlock();
            if (pcb.getResponseTime() == 0) {
                pcb.setResponseTime(curTime);
            }
            pcb.setWaitTime(curTime);
            if (pcb.getExecutionTime() > timeSlice) {
                int partialExecutionTime = pcb.getExecutionTime() - timeSlice;
                pcb.setAccumulatedTime(pcb.getExecutionTime());
                pcb.setExecutionTime(partialExecutionTime);
                //Context overhead.
                curTime += 2;
                curTime += timeSlice;
                m.try_lock();
                addReady(pcb, curTime);
                m.unlock();
            } else {
                //Context overhead.
                curTime += 1;
                pcb.setAccumulatedTime(pcb.getExecutionTime());
                curTime += pcb.getExecutionTime();
            }
            csv(fileName, pcb);
        } else if (isEmpty()) {
            m.unlock();
            break;
        }
    }
}

int RoundRobin::getTimeSlice() {
    return timeSlice;
}

void RoundRobin::setTimeSlice(int time) {
    timeSlice = time;
}

