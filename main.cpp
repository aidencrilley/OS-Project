#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int cTime, mainMem, numSerial, timeQ;

struct job {
    int time;
    int jobNum; 
    int mainMem; 
    int numSerial; 
    int runTime; 
    int priority;
};

queue<job> HoldQ1;
queue<job> HoldQ2;

void systemConfiguration(int t, int mM, int nS, int tQ) {
    cTime = t;
    mainMem = mM;
    numSerial = nS;
    timeQ = tQ;

    cout << "Time " << cTime << ' ' << "Mem " << mainMem << ' ' << "Serial " << numSerial << ' ' << "Quantum " << timeQ;
}

void jobArrival(int time, int jobNum, int mainMem, int numSerial, int runTime, int priority) {
    // Case 1: If there is not enough total main memory or total number of devices in the system for the job, 
    // the job is rejected never gets to one of the Hold Queues. 

    // Case 2: If  there  is  not  enough  available  main  memory  for  the  job,  the  job  is  put  in  one  of  the  Hold 
    // Queues, based on its priority, to wait for enough available main memory.

    // Case 3: If there is enough main memory for the job, then a process is created for the job, the required 
    // main memory is allocated to the process, and the process is put in the Ready Queue.  
}

void deviceRequest(int time, int jobNum, int numDevices) {

}

void deviceRelease(int time, int jobNum, int numDevices) {

}

void sysStatusDisplay(int time) {

}

int main() {

    ifstream inputfile;
    inputfile.open("input.txt");
    int procTable[100];
    int time = 0;
    char event = ' ';
    string input;

    while (getline(inputfile, input)) {

        if (input[0] == 'C') {

            int t, m, s, q;
            int stop; 

            for (int i = 0; i < input.size(); i++) {
                if (input[i] == 'M') {
                    stop = input.find(' ', i);
                    m = stoi(input.substr(i+2, stop));
                }
                else if (input[i] == 'S') {
                    stop = input.find(' ', i);
                    s = stoi(input.substr(i+2, stop));
                }
                else if (input[i] == 'Q') {
                    stop = input.find(' ', i);
                    q = stoi(input.substr(i+2, stop));
                }
            }

            systemConfiguration(input[2] - 48,m,s,q);
        }

        break;
    }

    inputfile.close();

    return 0;
} 

