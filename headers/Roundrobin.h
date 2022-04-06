#ifndef ROUNDROBINA_H
#define ROUNDROBINA_H

#include <string>
#include "PCBObject.h"
#include <iostream>
#include <fstream>
#include <queue>
#include "fcfs.h"
using namespace std;

class RoundRobin: public FCFS {

private:
    int timeSlice;
public :
    RoundRobin(int timeSlice);
    RoundRobin();
    RoundRobin(PCBObject pcb, int timeSlice);
    RoundRobin(queue<PCBObject> ready, int timeSlice);
    vector<int> run(string fileName, vector<int> curTime);
    int getTimeSlice();
    void setTimeSlice(int time);
};


#endif //ROUNDROBIN_H