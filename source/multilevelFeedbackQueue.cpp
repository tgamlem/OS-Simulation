#include "multilevelFeedbackQueue.h"
#include "fcfs.h"
#include "Roundrobin.h"
#include "PCBObject.h"

MultilevelFeedbackQueue::MultilevelFeedbackQueue(FCFS high, FCFS mid, RoundRobin low) {
    highPriority = high;
    midPriority = mid;
    lowPriority = low;
    timer = 0;
}

void MultilevelFeedbackQueue::addTime(int time) {
    timer += time;
    return;
}

int MultilevelFeedbackQueue::getTime() {
    return timer;
}

void MultilevelFeedbackQueue::raisePriority(PCBObject process) {
    if (process == midPriority.checkTop()) {
        highPriority.addReady(process, timer);
    } else if (process == lowPriority.checkTop()) {
        midPriority.addReady(process, timer);
    }
}

void MultilevelFeedbackQueue::lowerPriority(PCBObject process) {
    if (process == highPriority.checkTop()) {
        midPriority.addReady(process, timer);
    } else if (process == midPriority.checkTop()) {
        lowPriority.addReady(process, timer);
    }
}

FCFS MultilevelFeedbackQueue::getHighPriority() {
    return highPriority;
}

FCFS MultilevelFeedbackQueue::getMidPriority() {
    return midPriority;
}

RoundRobin MultilevelFeedbackQueue::getLowPriority() {
    return lowPriority;
}

FCFS MultilevelFeedbackQueue::getHighestQueue() {
    if (!highPriority.isEmpty()) {
        return highPriority;
    } else if (!midPriority.isEmpty()) {
        return midPriority;
    } else if (!lowPriority.isEmpty()) {
        return lowPriority;
    } else {
        return highPriority;
    }
}


vector<int> MultilevelFeedbackQueue::run(string fileName, vector<int> curTime) {
    while (!highPriority.isEmpty() || !midPriority.isEmpty() || !lowPriority.isEmpty()) {
        for (int i = 0; i < highPriority.getCPUCount(); i++) {
            auto currentQueue = getHighestQueue();
            auto pcb = currentQueue.checkTop();
            currentQueue.removeReady(curTime[i]);
            if (pcb.getExecutionTime() > timer) {
                int partialExecutionTime = pcb.getExecutionTime() - timer;
                pcb.setAccumulatedTime(pcb.getExecutionTime());
                pcb.setExecutionTime(partialExecutionTime);
                curTime[i] += timer;
                lowerPriority(pcb);
            } else {
                pcb.setAccumulatedTime(pcb.getExecutionTime());
                curTime[i] += pcb.getExecutionTime();
            }
            highPriority.csv(fileName, pcb);
        }
    }

    return curTime;
}
