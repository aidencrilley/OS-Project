#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
#include <deque>
#include <map>
using namespace std;

int CTIME = 1, MEMORY, SERIAL, QUANTUM;

struct Job {
    int time;
    int jobNum; 
    int mainMem; 
    int numSerial; 
    int runTime; 
    int priority;
};

deque<Job> HoldQ1; // FIFO
queue<Job> HoldQ2;
queue<Job> WaitQ;
queue<Job> ReadyQ;

map<int,int> allocation; // First int = Job #, Second int = allocated resources
map<int,int> need; // First int = Job #, Second int = resources needed

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

    //cout << "Time " << CTIME << ' ' << "Mem " << MEMORY << ' ' << "Serial " << SERIAL << ' ' << "Quantum " << QUANTUM << '\n';
}

void jobArrival(int time, int jN, int mM, int nS, int rT, int p) {

    Job j = jobCreate(time, jN, mM, nS, rT, p); // Creating a job when it arrives
    allocation.insert(pair<int,int>(jN,0)); // Recording the job's current resource allocation
    need.insert(pair<int,int>(jN,nS)); // Recording the job's current need
    cout << "Job #" << jN << " Need: " << need.at(jN) << '\n';

    // Case 1: If there is not enough total main memory or total number of devices in the system for the job, 
    // the job is rejected never gets to one of the Hold Queues. 
    if (j.mainMem > MEMORY || j.numSerial > SERIAL) {
        //cout << "Job rejected due to lack of resources/\n";
    }

    // Case 2: If  there  is  not  enough  available  main  memory  for  the  job,  the  job  is  put  in  one  of  the  Hold 
    // Queues, based on its priority, to wait for enough available main memory.
    else if (j.mainMem > MEMORY) {
        if (p == 1) {
            HoldQ1.push_back(j);
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

    //cout << "ARRIVAL -> Time: " << time << " Job # " << jN << " Memory: " << mM << " Serial: " << nS << " Runtime: " << rT << " Priority: " << p << '\n';
}

bool safetyCheck() {
    return false;
}

void deviceRequest(int time, int jobNum, int numDevices) {

    // A job can only request devices when it is running on the CPU
    Job j = ReadyQ.back();
    ReadyQ.pop();

    //cout << "JOB # -> " << jobNum << ' ';
    //cout << "NEED -> " << need.at(j.jobNum) << '\n';

    // Running Banker's Algorithm to check the request
    int available = SERIAL;

    if (j.numSerial < need.at(j.jobNum)) {

    }

    //cout << "REQUEST -> Time: " << time << " Job # " << jobNum << " Serial: " << numDevices << '\n';
}

void deviceRelease(int time, int jobNum, int numDevices) {

    //cout << "RELEASE -> Time: " << time << " Job # " << jobNum << " Serial: " << numDevices << '\n';
}

void sysStatusDisplay(int time) {
}

int getNum(string input, int index) {
    // Finding the index of a variable in the input, and then
    // reading the value it is set to and saving it
    int stop = input.find(' ', index);
    return stoi(input.substr(index+2, stop));
}

int main() {
    
    while(CTIME < 40) {
       
        ifstream inputfile;
        inputfile.open("input.txt");
        string input;

        while(getline(inputfile, input)){
            int stop = input.find(' ', 2);
            if(stoi(input.substr(2,stop)) == CTIME) {

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
        }
    
    inputfile.close();
    //cout << CTIME << endl;
    CTIME++;
    
    }

    return 0;
} 

