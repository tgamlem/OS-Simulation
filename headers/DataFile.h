#ifndef PROCESSDATAFILE_H
#define PROCESSDATAFILE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class DataFile {
    private:
        int PID;
        int arrivalTime;
        int executionTime;
        vector<int> cpuBurst;
        vector<int> ioBurst;
    public:
        DataFile(int curTime);
        string printFile();
        int getPID();
        int getArrivalTime();
        int getExecutionTime();
        vector<int> getCPUBursts();
        vector<int> getIOBursts();
        void setPID(int PID);
        void setArrivalTime(int time);
        void setExeuctionTime(int time);
        void addCPUBurst(int burst);
        void addIOBurst(int burst);
};

#endif