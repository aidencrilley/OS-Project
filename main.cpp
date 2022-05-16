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
    int devices; 
    int runTime;
    int timeAccrued;
    int timeFinished;
    int priority;
};

queue<Job> HoldQ1; // FIFO
deque<Job> HoldQ2;
queue<Job> WaitQ;
queue<Job> ReadyQ;
vector<Job> jobs;
vector<Job> FinishedJobs;

map<int,int> allocation; // First int = Job #, Second int = allocated resources
map<int,int> maxDevices; // First int = Job #, Second int = maximum resources
map<int,int> need; // First in = Job #, Second int = need

Job jobCreate(int time, int jN, int mM, int nS, int rT, int p) {
    Job j;
    j.time = time;
    j.jobNum = jN;
    j.mainMem = mM;
    j.devices = nS;
    j.runTime = rT;
    j.timeAccrued = 0;
    j.timeFinished = 0;
    j.priority = p;

    return j;
}

void systemConfiguration(int t, int mM, int nS, int tQ) {
    CTIME = t;
    MEMORY = mM;
    SERIAL = nS;
    QUANTUM = tQ;
}

void jobArrival(int time, int jN, int mM, int nS, int rT, int p) {

    Job j = jobCreate(time, jN, mM, nS, rT, p); // Creating a job when it arrives
    allocation.insert(pair<int,int>(jN,0)); // Recording the job's current resource allocation
    maxDevices.insert(pair<int,int>(jN,nS)); // Recording the job's maximum devices
    need.insert(pair<int,int>(jN,nS)); // Recording the job's current need
    jobs.push_back(j); // Adding job to a vector that keeps track of all jobs, will be used for safety check

    //cout << "Job #" << jN << " Need: " << maxDevices.at(jN) << '\n';

    // Case 1: If there is not enough total main memory or total number of devices in the system for the job, 
    // the job is rejected never gets to one of the Hold Queues. 
    if (j.mainMem > MEMORY || j.devices > SERIAL) {
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
            HoldQ2.push_back(j);
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

bool safetyCheck(int available, int allocation, int n) {
    
    // Checking the safety of the system
    bool safe = false;
    int m = available; // available resources
    bool finish[jobs.size()];

    int count = 0;

    for (int i = 0; i < jobs.size(); i++) {
        finish[i] = false;
    }

    while (count < jobs.size()) {
        for (int i = 0; i < jobs.size(); i++) {
            if (!finish[i] && n <= m) {
                m += allocation;
                finish[i] = true;

                if (need[i] -= 1 != 0)
                    need[i] -= 1;

                break;
            }
            count++;
        }
    }

    if (count == jobs.size()) {
        safe = true;
    }

    return safe;
}

void deviceRequest(Job j, int numDevices) {

    // Running Banker's Algorithm to check the request

    // 3 temp variables to pretend allocate resources
    int available = SERIAL;
    int alloc = allocation[j.jobNum];
    int max = maxDevices[j.jobNum];
    int n = need[j.jobNum];
    
    // STEP 1: Checking request <= need
    if (numDevices <= n) {
        // STEP 2: Checking request <= available devices
        if (numDevices <= available) {
            // STEP 3: Pretending to allocate resources and safety check
            available -= numDevices;
            alloc += j.devices;
            n -= j.devices;

            if (safetyCheck(available, alloc, n)) {
                // If the system is safe, allocate the resources and update the values
                SERIAL -= numDevices;
                allocation[j.jobNum] += numDevices;
                need[j.jobNum] -= numDevices;
                ReadyQ.push(j);
            }
            else {
                //cout << "This request would cause the system to become unsafe, and can not be granted.\n";
                WaitQ.push(j);
            }
        }
        
    }
    //cout << "REQUEST -> Time: " << time << " Job # " << jobNum << " Serial: " << numDevices << '\n';
}

void deviceRelease(Job j, int numDevices) {

    // Releasing devices and memory once the job comes off of the CPU
    SERIAL += numDevices;
    allocation[j.jobNum] -= numDevices;

    //cout << "RELEASE -> Time: " << time << " Job # " << jobNum << " Serial: " << numDevices << '\n';
}


/*
bool cpuCycle(Job j) {

    // Simulating once CPU cycle
    bool finish = false;
    if (j.runTime == j.timeAccrued) {
        j.timeFinished = CTIME;
        finish = true;
        FinishedJobs.push_back(j);
    }
    else {
        j.timeAccrued++;
        //cout << j.timeAccrued << endl;
    }
    return finish;
}
*/
void sysStatusDisplay(int time) {

    printf("At time %d: \n", time);
    printf("Current Available Main Memory = %d\n", MEMORY);
    printf("Current Devices = %d\n", SERIAL);
    printf("Completed Jobs:\n");
    printf("--------------------------------------------------------\n");
    printf("Job ID    Arrival Time    Finish Time    Turnaround Time\n");
    printf("========================================================\n");
    


    
    for (int i = 0; i < FinishedJobs.size(); i++) {
        printf("%d           %d               %d              %d\n", FinishedJobs[i].jobNum, FinishedJobs[i].time, FinishedJobs[i].timeFinished, FinishedJobs[i].timeFinished - FinishedJobs[i].time);
    }
    
    printf("\n");

    
    queue<Job> tempHold = HoldQ1;

    printf("Hold Queue 1:\n");
    printf("--------------------------------------------------------\n");
    printf("Job ID    Run Time\n");
    printf("========================================================\n");

    while(!tempHold.empty()) {
        printf("%d       %d\n", tempHold.front().jobNum, tempHold.front().runTime);
		tempHold.pop();
    }

    printf("\n");

    printf("Hold Queue 2:\n");
    printf("--------------------------------------------------------\n");
    printf("Job ID    Run Time\n");
    printf("========================================================\n");

    for(int i = 0;i<HoldQ2.size();i++) {
        printf("%d     %d\n", HoldQ2[i].jobNum, HoldQ2[i].runTime);
    }

    printf("\n");

    queue<Job> readyTemp = ReadyQ;
    
    printf("Ready Queue:\n");
    printf("--------------------------------------------------------\n");
    printf("Job ID    Run Time      Time Accrued\n");
    printf("========================================================\n");

    while(!readyTemp.empty()) {
        printf("%d       %d       %d\n", readyTemp.front().jobNum, readyTemp.front().runTime, readyTemp.front().timeAccrued);
		readyTemp.pop();
    }

    printf("\n");
    
}

int getNum(string input, int index) {
    // Finding the index of a variable in the input, and then
    // reading the value it is set to and saving it
    int stop = input.find(' ', index);
    return stoi(input.substr(index+2, stop));
}

int main() {
    int count = 0;
    while(CTIME < 10000) {
       
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

                    Job a;
                    for (int i = 0; i < jobs.size(); i++) {
                        if (jobs.at(i).jobNum == j) {
                            a = jobs.at(i);
                        }
                    }

                    if (input[0] == 'Q') {
                        deviceRequest(a,d);
                    }
                    else if (input[0] == 'L') {
                        deviceRelease(a,d);
                    }
                }

                else if (input[0] == 'D') {

                    int stop = input.find(' ', 2);
                    int t = stoi(input.substr(2, stop));
                    sysStatusDisplay(t);
                }
            }                   
        }
    
    inputfile.close();
    /*
    if(!ReadyQ.empty()){

        Job j = ReadyQ.front();
        ReadyQ.pop();
        if(count%QUANTUM < QUANTUM) {
            if(!cpuCycle(j)) {
                ReadyQ.push(j);
            }
        }
        count++;
        */ 
    CTIME++;
    
    }
    return 0;
} 

