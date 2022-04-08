#include <iostream>
#include "multilevelFeedbackQueue.h"
#include <thread>
#include <mutex>

#define CPUS 1
#define PROCESS_NUM 500
#define TIME_SLICE 10
string FILE_TYPE = "cores_1_quantum_10_.csv";
vector<int> currTime;
mutex m;

static void waitForThreadsAndOuputData(vector<std::thread> &threads) {
    for (int i = 0; i < CPUS; i++) {
        threads[i].join();
    }
    
    std::sort(currTime.begin(), currTime.end());
    std::cout << "Total Time: " << currTime[CPUS - 1] << endl;
    
    for (int i = 0; i < CPUS; i++) {
        std::cout << "CPU " << i << " current time is " << currTime[i] << endl;
    }
    
    threads.clear();
}

static void initCurrTime() {
    currTime.clear();
    for (int i = 0; i < CPUS; i++) {
        currTime.push_back(0);
    }
}

int main() {
    queue<PCBObject> processList;
    srand(time(NULL));
    for (int i = 0; i < PROCESS_NUM; i++) {
        auto dataFile = DataFile(0);
        processList.push(PCBObject(dataFile));
    }
    queue<PCBObject> processListRoundRobin = queue<PCBObject>(processList);
    queue<PCBObject> processListMultiLevelFeedback = queue<PCBObject>(processList);
    
    //Test FCFS:
    
    auto fcfs = FCFS(processList);
    fcfs.setCPUCount(CPUS);

    initCurrTime();
    vector<thread> threads;
    for (int i = 0; i < CPUS; i++) {
        threads.push_back(thread(&FCFS::run, &fcfs, "fcfs_" + FILE_TYPE, std::ref(currTime[i]), std::ref(m)));
    }
    waitForThreadsAndOuputData(threads);
    initCurrTime();
    auto roundRobin = RoundRobin(processListRoundRobin, TIME_SLICE);
    roundRobin.setCPUCount(CPUS);
    for (int i = 0; i < CPUS; i++) {
        threads.push_back(thread(&RoundRobin::run, &roundRobin, "RoundRobin_" + FILE_TYPE, std::ref(currTime[i]), std::ref(m)));
    }
    waitForThreadsAndOuputData(threads);
    initCurrTime();
    
     auto fcfsHigh = new FCFS(processListMultiLevelFeedback);
     fcfsHigh->setCPUCount(CPUS);
     auto fcfsMid = new FCFS();
     fcfsMid->setCPUCount(CPUS);
     auto roundRobinLow = new RoundRobin(TIME_SLICE);
    roundRobinLow->setCPUCount(CPUS);
     MultilevelFeedbackQueue multiLevelFeedback = MultilevelFeedbackQueue(fcfsHigh, fcfsMid, roundRobinLow);
    multiLevelFeedback.addTime(TIME_SLICE);
    for (int i = 0; i < CPUS; i++) {
        threads.push_back(thread(&MultilevelFeedbackQueue::run, &multiLevelFeedback, "multilevelFeedbackQueue" + FILE_TYPE, std::ref(currTime[i]), std::ref(m)));
    }
    waitForThreadsAndOuputData(threads);
    
    return 0;
}
