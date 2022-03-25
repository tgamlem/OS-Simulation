#include "PCBObject.h"

PCBObject::PCBObject(int PID, ProcessPriority priority, ProcessState state, int executionTime, int accumulatedTime, DataFile dataFile) {
    this->PID = PID;
    this->priority = priority;
    this->state = state;
    arrivalTime = 0;
    departureTime = 0;
    responseTime = 0;
    waitTime = 0;
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

void PCBObject::setArrivalTime(int time) {
    arrivalTime = time;
}

void PCBObject::setDepartureTime(int time) {
    departureTime = time;
}

void PCBObject::setResponseTime(int time) {
    responseTime = time - arrivalTime;
}

void PCBObject::setWaitTime(int time) {
    waitTime += time - arrivalTime;
}

void PCBObject::setAccumulatedTime(int time) {
    accumulatedTime = time;
}

int PCBObject::getArrivalTime() {
    return arrivalTime;
}

int PCBObject::getDepartureTime() {
    return departureTime;
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
