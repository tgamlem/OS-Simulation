#include "DataFile.h"
#include <cstdlib>
#include <chrono>
#include <sstream>

DataFile::DataFile(int curTime) {
    int pid = rand() % 30000 + 300;
    this->PID = pid;
    this->arrivalTime = curTime;
    this->executionTime = rand() % 20 + 1;
}

string DataFile::printFile() {
    stringstream ss;

    ss << PID << " " << arrivalTime << " ";
    for (int cpuBurst_i: cpuBurst) {
        ss << cpuBurst_i << " ";
    }
    for (int io_burst_i: ioBurst) {
        ss << io_burst_i << " ";
    }
    ss << endl;

    return ss.str();
}

int DataFile::getPID() {
    return PID;
}

int DataFile::getArrivalTime() {
    return arrivalTime;
}

int DataFile::getExecutionTime() {
    return executionTime;
}

vector<int> DataFile::getCPUBursts() {
    return cpuBurst;
}

vector<int> DataFile::getIOBursts() {
    return ioBurst;
}

void DataFile::setPID(int PID) {
    this->PID = PID;
}

void DataFile::setArrivalTime(int time) {
    this->arrivalTime = time;
}

void DataFile::setExeuctionTime(int time) {
    this->executionTime = time;
}

void DataFile::addCPUBurst(int burst) {
    cpuBurst.push_back(burst);
}

void DataFile::addIOBurst(int burst) {
    ioBurst.push_back(burst);
}
