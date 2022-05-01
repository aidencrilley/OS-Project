#include <iostream>
using namespace std;

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

void systemConfiguration(int time, int mainMem, int numSerial, int timeQ) {

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

    int procTable[100];
    int time = 0;
    char event = ' ';

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

    return 0;
}