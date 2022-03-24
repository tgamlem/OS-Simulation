#include "DataFile.h"
#include <cstdlib>
#include <chrono>
#include <sstream>

DataFile::DataFile() {
    // srandom();
    int pid = rand() % 30000 + 300;
    this->PID = pid;
    auto start = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(start);
    time = time + (rand() % 600);
    stringstream ss;
    ss << time;
    this->arrivalTime = ss.str();
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

string DataFile::getArrivalTime() {
    return arrivalTime;
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

void DataFile::setArrivalTime(string time) {
    this->arrivalTime = time;
}

void DataFile::addCPUBurst(int burst) {
    cpuBurst.push_back(burst);
}

void DataFile::addIOBurst(int burst) {
    ioBurst.push_back(burst);
}
