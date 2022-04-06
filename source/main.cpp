#include <iostream>
#include "multilevelFeedbackQueue.h"

#define CPUS 2
#define PROCESS_NUM 50
#define TIME_SLICE 4

int main() {
    queue<PCBObject> processList;
    int currTime = 0;
    for (int i = 0; i < PROCESS_NUM; i++) {
        auto dataFile = DataFile(currTime);
        processList.push(PCBObject(dataFile));
    }
    queue<PCBObject> processListRoundRobin = queue<PCBObject>(processList);
    queue<PCBObject> processListMultiLevelFeedback = queue<PCBObject>(processList);
    
    //Test FCFS:
    
    auto fcfs = FCFS(processList);
    fcfs.setCPUCount(CPUS);
    vector<int> cpus;
    for (int i = 0; i < CPUS; i++) {
        cpus.push_back(currTime);
    }

    while (fcfs.isEmpty() == false) {
        cout << processList.size() << endl;
        cpus = fcfs.run("fcfs.csv", cpus);
    }
    for (int i = 0; i < CPUS; i++) {
        cout << "CPU " << i << " is " << cpus[i] << endl;
    }
    cpus.clear();
    for (int i = 0; i < CPUS; i++) {
        cpus.push_back(currTime);
    }
    auto roundRobin = RoundRobin(processListRoundRobin, TIME_SLICE);
    roundRobin.setCPUCount(CPUS);
    //set cpu cont here!!
    while (roundRobin.isEmpty() == false) {
        cout << processListRoundRobin.size() << endl;
        cpus = roundRobin.run("roundRobin.csv", cpus);
    }
    for (int i = 0; i < CPUS; i++) {
        cout << "CPU " << i << " is " << cpus[i] << endl;
    }
    cpus.clear();
    for (int i = 0; i < CPUS; i++) {
        cpus.push_back(currTime);
    }
    auto fcfsHigh = FCFS(processListMultiLevelFeedback);
    fcfsHigh.setCPUCount(CPUS);
    auto fcfsLow = FCFS();
    fcfsLow.setCPUCount(CPUS);
    auto roundRobinLow = RoundRobin(TIME_SLICE);
    roundRobin.setCPUCount(CPUS);

    MultilevelFeedbackQueue multiLevelFeedback = MultilevelFeedbackQueue(fcfsHigh, fcfsLow, roundRobinLow);
    multiLevelFeedback.run("multiLevelFeedback.csv", cpus);
    for (int i = 0; i < CPUS; i++) {
        cout << "CPU " << i << " is " << cpus[i] << endl;
    }
    return 0;
}