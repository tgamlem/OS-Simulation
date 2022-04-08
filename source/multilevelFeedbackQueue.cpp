#include "multilevelFeedbackQueue.h"
#include "fcfs.h"
#include "Roundrobin.h"
#include "PCBObject.h"

MultilevelFeedbackQueue::MultilevelFeedbackQueue(FCFS * high, FCFS * mid, RoundRobin * low) {
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

//void MultilevelFeedbackQueue::raisePriority(PCBObject process) {
//    if (process == midPriority.checkTop()) {
//        highPriority.addReady(process, timer);
//    } else if (process == lowPriority.checkTop()) {
//        midPriority.addReady(process, timer);
//    }
//}

void MultilevelFeedbackQueue::lowerPriority(PCBObject process) {
    if (process.getPriority() == PPHigh) {
        process.setPriority(PPMedium);
        midPriority->addReady(process, timer);
    } else if (process.getPriority() == PPMedium) {
        process.setPriority(PPLow);
        lowPriority->addReady(process, timer);
    }
}

FCFS * MultilevelFeedbackQueue::getHighPriority() {
    return highPriority;
}

FCFS * MultilevelFeedbackQueue::getMidPriority() {
    return midPriority;
}

RoundRobin * MultilevelFeedbackQueue::getLowPriority() {
    return lowPriority;
}

FCFS * MultilevelFeedbackQueue::getHighestQueue() {
    if (!highPriority->isEmpty()) {
        return highPriority;
    } else if (!midPriority->isEmpty()) {
        return midPriority;
    } else if (!lowPriority->isEmpty()) {
        return lowPriority;
    } else {
        return highPriority;
    }
}


void MultilevelFeedbackQueue::run(string fileName, int& curTime, mutex& m) {
    while (!highPriority->isEmpty() || !midPriority->isEmpty() || !lowPriority->isEmpty()) {
        if(m.try_lock()) {
            auto currentQueue = getHighestQueue();
            auto pcb = currentQueue->checkTop();
            currentQueue->removeReady(curTime);
            if (pcb.getResponseTime() == 0) {
                pcb.setResponseTime(curTime);
            }
            pcb.setWaitTime(curTime);
            m.unlock();
            if (pcb.getExecutionTime() > timer) {
                int partialExecutionTime = pcb.getExecutionTime() - timer;
                pcb.setAccumulatedTime(pcb.getExecutionTime());
                pcb.setExecutionTime(partialExecutionTime);
                curTime += timer;
                //Context overhead.
                curTime += 3;
                m.try_lock();
                lowerPriority(pcb);
                m.unlock();
            } else {
                pcb.setAccumulatedTime(pcb.getExecutionTime());
                curTime += pcb.getExecutionTime();
                //Context overhead.
                curTime += 1;
            }
            currentQueue->csv(fileName, pcb);
        }
    }
}
