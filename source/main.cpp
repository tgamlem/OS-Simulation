#include <iostream>
#include "multilevelFeedbackQueue.h"
#include <thread>
#include <mutex>

#define CPUS 4
#define PROCESS_NUM 500
#define TIME_SLICE 15
string FILE_TYPE = "cores_4_quantum_15_.csv";
vector<int> currTime;
mutex m;

void calculateAverages(string readFileName, string writeFileName, int totalTime);

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
    calculateAverages("fcfs_" + FILE_TYPE, "fcfs_averages_" + FILE_TYPE, currTime[0]);
    initCurrTime();
    auto roundRobin = RoundRobin(processListRoundRobin, TIME_SLICE);
    roundRobin.setCPUCount(CPUS);
    for (int i = 0; i < CPUS; i++) {
        threads.push_back(thread(&RoundRobin::run, &roundRobin, "RoundRobin_" + FILE_TYPE, std::ref(currTime[i]), std::ref(m)));
    }
    waitForThreadsAndOuputData(threads);
    calculateAverages("RoundRobin_" + FILE_TYPE, "RoundRobin_averages_" + FILE_TYPE, currTime[0]);
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
        threads.push_back(thread(&MultilevelFeedbackQueue::run, &multiLevelFeedback, "multilevelFeedbackQueue_" + FILE_TYPE, std::ref(currTime[i]), std::ref(m)));
    }
    waitForThreadsAndOuputData(threads);
    calculateAverages("multilevelFeedbackQueue_" + FILE_TYPE, "multilevelFeedbackQueue_averages_" + FILE_TYPE, currTime[0]);

    return 0;
}

void calculateAverages(string readFileName, string writeFileName, int totalTime) {
    vector<int> response;
    vector<int> wait;
    vector<int> acc;
    int avgResponse = 0;
    int avgWait = 0;
    int avgAcc = 0;

    ifstream read(readFileName);
    string a,b,c,d;
    while(read >> a >> b >> c >> d) {
        response.push_back(stoi(b));
        wait.push_back(stoi(c));
        acc.push_back(stoi(d));
    }
    read.close();

    // calculate averages
    for (int i = 0; i < response.size(); i++) {
        avgResponse += response[i];
    }
    avgResponse /= response.size();


    for (int i = 0; i < wait.size(); i++) {
        avgWait += wait[i];
    }
    avgWait /= wait.size();


    for (int i = 0; i < acc.size(); i++) {
        avgAcc += acc[i];
    }
    avgAcc /= acc.size();

    totalTime /= PROCESS_NUM;

    ofstream write(writeFileName);
    write << avgResponse << "," << avgWait << "," << avgAcc << "," << totalTime << "," << endl;
    write.close();

    return;
}
