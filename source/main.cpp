#include <iostream>
#include "multilevelFeedbackQueue.h"
#include <thread>
#include <mutex>

#define CPUS 2
#define PROCESS_NUM 50
#define TIME_SLICE 4

vector<int> currTime;
mutex m;

int main() {
    queue<PCBObject> processList;
    for (int i = 0; i < PROCESS_NUM; i++) {
        auto dataFile = DataFile(0);
        processList.push(PCBObject(dataFile));
    }
    queue<PCBObject> processListRoundRobin = queue<PCBObject>(processList);
    queue<PCBObject> processListMultiLevelFeedback = queue<PCBObject>(processList);
    
    //Test FCFS:
    
    auto fcfs = FCFS(processList);
    fcfs.setCPUCount(CPUS);

    for (int i = 0; i < CPUS; i++) {
        currTime.push_back(0);
    }
    vector<thread> threads;
    for (int i = 0; i < CPUS; i++) {
        threads.push_back(thread(&FCFS::run, &fcfs, "fcfs.csv", std::ref(currTime[i]), std::ref(m)));
    }
    for (int i = 0; i < CPUS; i++) {
        threads[i].join();
    }

    std::sort(currTime.begin(), currTime.end());

    std::cout << "Total Time: " << currTime[CPUS - 1] << endl;

    for (int i = 0; i < CPUS; i++) {
        std::cout << "CPU " << i << " current time is " << currTime[i] << endl;
    }
    // cpus.clear();
    // for (int i = 0; i < CPUS; i++) {
    //     cpus.push_back(currTime);
    // }
    // auto roundRobin = RoundRobin(processListRoundRobin, TIME_SLICE);
    // roundRobin.setCPUCount(CPUS);
    // //set cpu cont here!!
    // while (roundRobin.isEmpty() == false) {
    //     cout << processListRoundRobin.size() << endl;
    //     cpus = roundRobin.run("roundRobin.csv", cpus);
    // }
    // for (int i = 0; i < CPUS; i++) {
    //     cout << "CPU " << i << " is " << cpus[i] << endl;
    // }
    // cpus.clear();
    // for (int i = 0; i < CPUS; i++) {
    //     cpus.push_back(currTime);
    // }
    // auto fcfsHigh = FCFS(processListMultiLevelFeedback);
    // fcfsHigh.setCPUCount(CPUS);
    // auto fcfsLow = FCFS();
    // fcfsLow.setCPUCount(CPUS);
    // auto roundRobinLow = RoundRobin(TIME_SLICE);
    // roundRobin.setCPUCount(CPUS);

    // MultilevelFeedbackQueue multiLevelFeedback = MultilevelFeedbackQueue(fcfsHigh, fcfsLow, roundRobinLow);
    // multiLevelFeedback.run("multiLevelFeedback.csv", cpus);
    // for (int i = 0; i < CPUS; i++) {
    //     cout << "CPU " << i << " is " << cpus[i] << endl;
    // }
    return 0;
}
