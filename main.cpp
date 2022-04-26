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

void systemConfiguration() {

}

void jobArrival() {

}

void deviceRequest() {

}

void deviceRelease() {

}

void sysStatusDisplay() {

}

int main() {

    int procTable[100];
    char event = ' ';

    switch(event) {
        case 'C':
            systemConfiguration();
            break;
        case 'A':
            jobArrival();
            break;
        case 'Q':
            deviceRequest();
            break;
        case 'L':
            deviceRelease();
            break;
        case 'D':
            sysStatusDisplay();
            break;
    }

    return 0;
}