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
        lowerPriority.addReady(process, timer);
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
