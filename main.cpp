#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

int cTime, mainMem, numSerial, timeQ;

class HoldQ1 {
    public:
        int value;
        HoldQ1* next;
};

class HoldQ2 {
    public:
        int value;
        HoldQ2* next;
};

void systemConfiguration(int t, int mM, int nS, int tQ) {
    cTime = t;
    mainMem = mM;
    numSerial = nS;
    timeQ = tQ;
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
        
        int i = 0;
        int n = input.length();
        char *output[10];
        char *ptr;
        char char_array[n+1];
        strcpy(char_array, input.c_str());
        ptr = strtok(char_array, " ");
        
        while (ptr!= NULL) {
            output[i] = ptr;   
            ptr = strtok (NULL, " , ");  
            i+=1;
        }
        
        for(int j = 0;j<i; j++) {
            cout << output[j][0] << '\n';
            if (output[j][0] == 'C') {
                systemConfiguration(output[1][-1], output[2][-1], output[3][-1], output[4][-1]);
            }
        }
        

    }

    inputfile.close();

    return 0;
}

