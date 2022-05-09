#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

int cTime, mainMem, numSerial, timeQ;

struct Job {
    int time;
    int jobNum; 
    int mainMem; 
    int numSerial; 
    int runTime; 
    int priority;
};

queue<Job> HoldQ1;
queue<Job> HoldQ2;

Job jobCreate(int time, int jN, int mM, int nS, int rT, int p) {
    Job j;
    j.time = time;
    j.jobNum = jN;
    j.mainMem = mM;
    j.numSerial = nS;
    j.runTime = rT;
    j.priority = p;

    return j;
}

void systemConfiguration(int t, int mM, int nS, int tQ) {
    cTime = t;
    mainMem = mM;
    numSerial = nS;
    timeQ = tQ;

    cout << "Time " << cTime << ' ' << "Mem " << mainMem << ' ' << "Serial " << numSerial << ' ' << "Quantum " << timeQ;
}

void jobArrival(int time, int jN, int mM, int nS, int rT, int p) {
    Job j = jobCreate(time, jN, mM, nS, rT, p);

    // Case 1: If there is not enough total main memory or total number of devices in the system for the job, 
    // the job is rejected never gets to one of the Hold Queues. 
    if (mM > mainMem || nS > numSerial) {
        cout << "Job rejected due to lack of resources/\n";
    }

    // Case 2: If  there  is  not  enough  available  main  memory  for  the  job,  the  job  is  put  in  one  of  the  Hold 
    // Queues, based on its priority, to wait for enough available main memory.
    else if (mM > mainMem) {
        if (p == 1) {

        }
        else if (p == 2) {

        }
    }

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

            stop = input.find(' ', 1);
            t = stoi(input.substr(2, stop));


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

            systemConfiguration(t,m,s,q);
        }

        else if (input[0] == 'A') {

        }

        break;
    }

    inputfile.close();

    return 0;
} 

