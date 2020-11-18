#include <iostream>
#include <string>
#include "Registrar.h"
using namespace std;
int main(int argc, char** argv) {
    Registrar r;
//if file is not ran in console
    if(argc < 2) {
        cout << "No file ran in console" << endl;
    }
//if they run file in console
    else if(argc >= 2) {
        string file = argv[1];
        int currTime = 0;
        int openWindows = 0;
        bool fileAccepted = true;
//file from console
        if(r.importFile(file)) {
            while(fileAccepted) {
                if(r.studentQueue.isEmpty()) {
                    int hold = 0;
                    for(int i = 0; i < r.openWindows; ++i) {
                        if((r.windowArray[i]->windowTime) < 1) {
                            hold++;
                        }
                    }
                    if(hold == r.openWindows) {
                        fileAccepted = false;
                    }
                }
//orangizes studetns to window
                for(int i = 0; i < r.openWindows; ++i) {
                    if(r.windowArray[i]->windowTime < 1) {
                        if(!r.studentQueue.isEmpty()) {
                            StudentTime* student = r.studentQueue.vFront();
                            if(student->entryTime <= currTime) {
                                if(r.windowArray[i]->idleTime > 0) {
                                    r.idleData.enqueue(r.windowArray[i]->idleTime);
                                }
                                r.windowArray[i] = r.studentQueue.dequeue();
                                r.waitingData.enqueue(r.windowArray[i]->waitTime);
                            }
                        }
                    }
                }
//Ticks
                currTime++;
                r.clockTick(currTime);
            }
//empty windows
            for(int i = 0; i < r.openWindows; ++i) {
                if(r.windowArray[i]->idleTime > 0) {
                    r.idleData.enqueue(r.windowArray[i]->idleTime);
                }
            }
//text that will be outputted of data
            cout << "The mean student wait time: " << r.meanTime() << endl;
            cout << "The median student wait time: " << r.medianTime() << endl;
            cout << "The longest student wait time: " << r.longestTime() << endl;
            cout << "The number of studdnts waiting over 10 minutes: " << r.overTime() << endl;
            cout << "The longest window idle time: " << r.longestIdleTime() << endl;
            cout << "Number of windows idle for over 5 minutes: " << r.idleOverTime() << endl;
        }
    }
    return 0;
}
