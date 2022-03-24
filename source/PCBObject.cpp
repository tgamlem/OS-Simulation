#include "PCBObject.h"

PCBObject::PCBObject(int PID, ProcessPriority priority, ProcessState state, int executionTime, int accumulatedTime, DataFile dataFile) {
    this->PID = PID;
    this->priority = priority;
    this->state = state;
    this->executionTime = executionTime;
    this->accumulatedTime = accumulatedTime;
    this->dataFile = dataFile;
}

int PCBObject::getPID() {
    return PID;
}

ProcessPriority PCBObject::getPriority() {
    return priority;
}

ProcessState PCBObject::getState() {
    return state;
}

int PCBObject::getExecutionTime() {
    return executionTime;
}

int PCBObject::getAccumulatedTime() {
    return accumulatedTime;
}

DataFile PCBObject::getDataFile() {
    return dataFile;
}

void PCBObject::setDataFile(DataFile dataFile) {
    this->dataFile = dataFile;
}

void PCBObject::setPriority(ProcessPriority priority) {
    this->priority = priority;
}

void PCBObject::setState(ProcessState state) {
    this->state = state;
}

void PCBObject::updateAccumulateTime(int accumulatedTime) {
    this->accumulatedTime = accumulatedTime;
}
