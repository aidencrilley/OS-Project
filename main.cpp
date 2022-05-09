#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
#include <map>
using namespace std;

int CTIME, MEMORY, SERIAL, QUANTUM;

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
queue<Job> WaitQ;
queue<Job> ReadyQ;

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
    CTIME = t;
    MEMORY = mM;
    SERIAL = nS;
    QUANTUM = tQ;

    cout << "Time " << CTIME << ' ' << "Mem " << MEMORY << ' ' << "Serial " << SERIAL << ' ' << "Quantum " << QUANTUM << '\n';
}

void jobArrival(int time, int jN, int mM, int nS, int rT, int p) {
    Job j = jobCreate(time, jN, mM, nS, rT, p);

    // Case 1: If there is not enough total main memory or total number of devices in the system for the job, 
    // the job is rejected never gets to one of the Hold Queues. 
    if (j.mainMem > MEMORY || j.numSerial > SERIAL) {
        //cout << "Job rejected due to lack of resources/\n";
    }

    // Case 2: If  there  is  not  enough  available  main  memory  for  the  job,  the  job  is  put  in  one  of  the  Hold 
    // Queues, based on its priority, to wait for enough available main memory.
    else if (j.mainMem > MEMORY) {
        if (p == 1) {
            HoldQ1.push(j);
            //cout << "Job placed in Hold Queue 1\n";
        }
        else if (p == 2) {
            HoldQ2.push(j);
            //cout << "Job placed in Hold Queue 2\n";
        }
    }

    // Case 3: If there is enough main memory for the job, then a process is created for the job, the required 
    // main memory is allocated to the process, and the process is put in the Ready Queue.  
    else if (j.mainMem < MEMORY) {
        MEMORY -= j.mainMem;
        ReadyQ.push(j);
        //cout << "Job placed in Ready Queue\n";
    }

    cout << "ARRIVAL -> Time: " << time << " Job # " << jN << " Memory: " << mM << " Serial: " << nS << " Runtime: " << rT << " Priority: " << p << '\n';
}

void deviceRequest(int time, int jobNum, int numDevices) {

    cout << "REQUEST -> Time: " << time << " Job # " << jobNum << " Serial: " << numDevices << '\n';
}

void deviceRelease(int time, int jobNum, int numDevices) {

    cout << "RELEASE -> Time: " << time << " Job # " << jobNum << " Serial: " << numDevices << '\n';
}

void sysStatusDisplay(int time) {

}

int getNum(string input, int index) {
    int stop = input.find(' ', index);
    return stoi(input.substr(index+2, stop));
}

int main() {

    ifstream inputfile;
    inputfile.open("input.txt");
    int procTable[100];
    int time = 0;
    char event = ' ';
    string input;
    int i = 0;

    while (getline(inputfile, input)) {

        if (input[0] == 'C') {

            int t, m, s, q;
            int stop; 

            stop = input.find(' ', 2);
            t = stoi(input.substr(2, stop));

            for (int i = 0; i < input.size(); i++) {
                if (input[i] == 'M') {
                    m = getNum(input, i);
                }
                else if (input[i] == 'S') {
                    s = getNum(input, i);
                }
                else if (input[i] == 'Q') {
                    q = getNum(input, i);
                }
            }

            systemConfiguration(t, m, s, q);
        }

        else if (input[0] == 'A') {

            int t, j, m, s, r, p;
            int stop;

            stop = input.find(' ', 2);
            t = stoi(input.substr(2, stop));

            for (int i = 0; i < input.size(); i++) {
                if (input[i] == 'J') {
                    j = getNum(input, i);
                }
                else if (input[i] == 'M') {
                    m = getNum(input, i);
                }
                else if (input[i] == 'S') {
                    s = getNum(input, i);
                }
                else if (input[i] == 'R') {
                    r = getNum(input, i);
                }
                else if (input[i] == 'P') {
                    p = getNum(input, i);
                }
            }

            jobArrival(t, j, m, s, r, p);
        }

        else if (input[0] == 'Q' || input[0] == 'L') {

            int t, j, d;
            int stop;

            stop = input.find(' ', 2);
            t = stoi(input.substr(2, stop));

            for (int i = 0; i < input.size(); i++) {
                if (input[i] == 'J') {
                    j = getNum(input, i);
                }
                else if (input[i] == 'D') {
                    d = getNum(input, i);
                }
            }

            if (input[0] == 'Q') {
                deviceRequest(t,j,d);
            }
            else if (input[0] == 'L') {
                deviceRelease(t,j,d);
            }
        }
    }

    inputfile.close();

    return 0;
} 

