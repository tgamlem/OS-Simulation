#include "PCBObject.h"
#include <iostream>

PCBObject::PCBObject(DataFile dataFile) {
    PID = dataFile.getPID();
    arrivalTime = dataFile.getArrivalTime();
    departureTime = 0;
    responseTime = 0;
    waitTime = 0;
    executionTime = dataFile.getExecutionTime();
    accumulatedTime = 0;
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

void PCBObject::print() {
    std::cout << "---------------------------------\n";
    std::cout << "PCB Object:\n";
    std::cout << "\tPID: " << PID << endl;
    std::cout << "\tArrival Time: " << arrivalTime << endl;
    std::cout << "\tResponse Time: " << responseTime << endl;
    std::cout << "\tWait Time: " << waitTime << endl;
    std::cout << "\tExecution Time: " << executionTime << endl;
    std::cout << "\tAccumulated Time: " << accumulatedTime << endl;
    std::cout << "\tDeparture Time: " << departureTime << endl;
    std::cout << "---------------------------------\n\n";
}

bool PCBObject::operator==(const PCBObject& pcb) {
    if (this->PID == pcb.PID) {
        return true;
    } else {
        return false;
    }
void PCBObject::setExecutionTime(int time) {
    executionTime = time;
}

int PCBObject::getResponseTime() {
    return responseTime;
}
