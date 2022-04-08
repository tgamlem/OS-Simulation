#ifndef PCBOBJECT_H
#define PCBOBJECT_H
#include <string>
#include <iostream>
#include <vector>
#include "DataFile.h"
using namespace std;

enum ProcessState {
    PSNew,
    PSReady,
    PSRunning,
    PSBlocked,
    PSExit
};

enum ProcessPriority {
    PPHigh,
    PPMedium,
    PPLow
};

class PCBObject {
    private:
        int PID;
        ProcessPriority priority;
        ProcessState state;
        int arrivalTime;
        int departureTime;
        int responseTime;
        int waitTime;
        int executionTime;
        int accumulatedTime;
        DataFile dataFile;
    public:
        // Constructor
        PCBObject(DataFile dataFile);
        // Getters and Setters:
        int getPID();
        ProcessPriority getPriority();
        ProcessState getState();
        void setArrivalTime(int time);
        void setExecutionTime(int time);
        void setDepartureTime(int time);
        void setResponseTime(int time);
        void setWaitTime(int time);
        void setAccumulatedTime(int time);
        int getArrivalTime();
        int getDepartureTime();
        int getExecutionTime();
        int getAccumulatedTime();
        int getResponseTime();
        int getWaitTime();
        DataFile getDataFile();
        void setDataFile(DataFile dataFile);
        void setPriority(ProcessPriority priority);
        void setState(ProcessState state);
        void print();
        bool operator==(const PCBObject& pcb) const;
};

#endif
