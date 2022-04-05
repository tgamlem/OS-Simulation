#ifndef ROUNDROBINA_H
#define ROUNDROBINA_H

#include <string>
#include <list>
#include "PCBObject.h"
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

class Roundrobin {

private:
    int lastArrival;
    int CPUtimer;
public :
    int newArrival;
    int turnAroundTimeSum;
    int waitingTimeSum;
    int pcbObjectCount;
    int totalTimeCount;

    //Constructor
    Roundrobin();

    
	// Gets data from the file and puts into a list 
    void getFileData(string);

    //goes through text and gets the data from the file
    //to make a Process object

	// goes through the text and gets the data from the file to make a process object
    PCBObject makeProcess(string s);


	//puts the PCB objects in an array and then uses a min queue to process them.
    void putProcessInArray(list <PCBObject> p);

    //calculates turn around time
    double getAverageTurnaroundtime();

    //calculates average wait time
    double getAverageWaitingTime();

    //calculates throughput
    double getThroughput();
};


#endif //ROUNDROBIN_H