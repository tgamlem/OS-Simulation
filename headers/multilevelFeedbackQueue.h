#ifndef MULTILEVELFEEDBACKQUEUE_H
#define MULTILEVELFEEDBACKQUEUE_H

#include "fcfs.h"
#include "Roundrobin.h"
#include "PCBObject.h"

class MultilevelFeedbackQueue {
    private:
        int timer;
        FCFS highPriority;
        FCFS midPriority;
        RoundRobin lowPriority;
    public:
        // Constructor
        MultilevelFeedbackQueue(FCFS high, FCFS mid, RoundRobin low);
        // add time to timer
        void addTime(int time);
        // get current time
        int getTime();
        // move process from lower priority to higher priority
        void raisePriority(PCBObject process);
        // move process from high priority to lower priority
        void lowerPriority(PCBObject process);
        // getter for high priority queue
        FCFS getHighPriority();
        // getter for mid priority queue
        FCFS getMidPriority();
        // getter for low priority queue
        RoundRobin getLowPriority();

        vector<int> run(string fileName, vector<int> currTime);
        FCFS getHighestQueue();
};

#endif