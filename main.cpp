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
            cout << output[j][0] << "\n";
        }
        

    }

    switch(event) {
        case 'C':
            //systemConfiguration();
            break;
        case 'A':
            //jobArrival();
            break;
        case 'Q':
            //deviceRequest();
            break;
        case 'L':
            //deviceRelease();
            break;
        case 'D':
            //sysStatusDisplay();
            break;
    }

    inputfile.close();

    return 0;
}

