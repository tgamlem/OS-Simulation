#include <string>
#include <iostream>
#include "PCBObject.h"
#include <fstream>
#include <list>
#include <iterator>
#include <typeinfo>
#include "DataFile.h"
#include <queue>
#include "Roundrobin.h"


//Constructor
Roundrobin::Roundrobin() {
    lastArrival = -1;
    CPUtimer = -1; //time has not started
    turnAroundTimeSum = 0;
    waitingTimeSum = 0;
    pcbObjectCount = 0; 
    totalTimeCount = 0;
    newArrival = -1;

}

//Gets the data from the file and puts into a list of PCB Objects
void Roundrobin::getFileData(string fileName) {
	//Prints out all the values from the file
    ifstream afile;
    string line;
    afile.open(fileName); 
    list <PCBObject> alist;
    //makes each line a process
    while (afile >> line) {
        pcbObjectCount++;
        alist.push_back(makeProcess(line));
    }
    newArrival = pcbObjectCount;
	//Do a array of size , then last arrival and fill it with the PCB objects

    putProcessInArray(alist);
    list<PCBObject>::iterator itr;

    //makes min heap
	// if time is equal or less, sets up min heap logic

}

//puts all the PCBObject in an array and then
//uses a minqueue to process them.
void Roundrobin::putProcessInArray(list <PCBObject> alist) {
    //make array of lists
    list <PCBObject> allPCBObject[lastArrival + 1];
    //fills array with empty list
    for (int i = 0; i < lastArrival + 1; i++) {
        list <PCBObject> temp;
        allPCBObject[i] = temp;
    }


	// puts the PCB objects in a array based on arrival time
    list<PCBObject>::iterator itr;
    for (itr = alist.begin(); itr != alist.end(); ++itr) {
        allPCBObject[itr->getArrivalTime()].push_back(*itr);
    }

	// Initializes a minimum heap and puts all the PCB object at 0
    int beg = 0;
    CPUtimer++;
    priority_queue <PCBObject> q;
    while (CPUtimer <= lastArrival) {
        for (int i = beg; i <= CPUtimer; i++) {
            if (allPCBObject[i].empty()) {
                //do nothing
            } else {
                //add it to the queue
                list<PCBObject>::iterator itr2;
                for (itr2 = allPCBObject[i].begin(); itr2 != allPCBObject[i].end(); ++itr2) {
                    q.push(*itr2);
                }
            }
        }

		
        PCBObject tempP = q.top();
        DataFile fileP;

        tempP.print();
        beg = CPUtimer + 1;
        CPUtimer = CPUtimer + 1;
        //subtracts time unit from top
        fileP.cpuBurst = fileP.cpuBurst - 1;
		//pops if its greater than 0 then it adds it back in, if it is equal to 0 it wont add it	
        if (fileP.cpuBurst == 0) {
            turnAroundTimeSum = turnAroundTimeSum + (CPUtimer - tempP.arrivalTime);
            totalTimeCount = CPUtimer;
            int turnaroundtime = CPUtimer - tempP.arrivalTime;
            int waitingtime = turnaroundtime - tempP.tempcpuBurst;
            waitingTimeSum = waitingTimeSum + waitingtime;
            q.pop();
        } else {
            q.pop();
            newArrival = CPUtimer;
            tempP.priority = -1; // First appears
            tempP.tempArrivalTime = newArrival;
            q.push(tempP);
        }
    }

    //Pops left
    while (!q.empty()) {
        PCBObject tempP = q.top();
        tempP.print();
        CPUtimer = CPUtimer + 1;
        //Subtracts time unit for the top
        tempP.cpuBurst = tempP.cpuBurst - 1;
		//pops if its greater than 0 then it adds it back in, if it is equal to 0 it wont add it
        if (tempP.cpuBurst == 0) {
            turnAroundTimeSum = turnAroundTimeSum + (CPUtimer - tempP.arrivalTime);
            totalTimeCount = CPUtimer;
            int turnaroundtime = CPUtimer - tempP.arrivalTime;
            int waitingtime = turnaroundtime - tempP.tempcpuBurst;
            waitingTimeSum = waitingTimeSum + waitingtime;
            q.pop();
        } else {
            q.pop();
            newArrival = CPUtimer;
            tempP.priority = -1;
            tempP.tempArrivalTime = newArrival;
            q.push(tempP);
        }
    }
    return;
}


//goes through the text and gets data from the data file and makes pcb object
PCBObject Roundrobin::makeProcess(string line) {
    int commas = 0;
    string v1 = "";
    string v2 = "";
    string v3 = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',') {
            commas++;
        } else {
            if (commas == 0) {
                v1 = v1 + line.at(i);
            } else if (commas == 1) {
                v2 = v2 + line.at(i);
            } else {
                v3 = v3 + line.at(i);
            }
        }

    }
    PCBObject p(stoi(v1), stoi(v2), stoi(v3));
//find out last arrival
    if (stoi(v3) > lastArrival) {
        lastArrival = stoi(v3);
    }

//	p.printFile();
    return p;
}

//calculates the turnaroundtime
double Roundrobin::getAverageTurnaroundtime() {
    double ans = (double(turnAroundTimeSum) / double(pcbObjectCount));

    return ans;
}


// calculates the average wait time
double Roundrobin::getAverageWaitingTime() {
    double ans = (double(waitingTimeSum) / double(pcbObjectCount));
    
    return ans;
}

//Calculates the throughput
double Roundrobin::getThroughput() {
    double ans = (double(pcbObjectCount) / double(totalTimeCount));
    return ans;
}