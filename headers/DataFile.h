#ifndef PROCESSDATAFILE_H
#define PROCESSDATAFILE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class DataFile {
    private:
        int PID;
        string arrivalTime;
        vector<int> cpuBurst;
        vector<int> ioBurst;
    public:
        DataFile();
        string printFile();
        int getPID();
        string getArrivalTime();
        vector<int> getCPUBursts();
        vector<int> getIOBursts();
        void setPID(int PID);
        void setArrivalTime(string time);
        void addCPUBurst(int burst);
        void addIOBurst(int burst);
};

#endif