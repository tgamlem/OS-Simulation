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
        int executionTime;
        int accumulatedTime;
        DataFile dataFile;
    public:
        // Constructor
        PCBObject(int PID, ProcessPriority priority, ProcessState state, int executionTime, int accumulatedTime, DataFile dataFile);
        // Getters and Setters:
        int getPID();
        ProcessPriority getPriority();
        ProcessState getState();
        int getExecutionTime();
        int getAccumulatedTime();
        DataFile getDataFile();
        void setDataFile(DataFile dataFile);
        void setPriority(ProcessPriority priority);
        void setState(ProcessState state);
        void updateAccumulateTime(int accumulatedTime);
};

#endif