#include <iostream>
#include <fstream>
#include <string>
#include <queue>
//#include <algorithm>
//include <sstream>
#include "Registrar.h"
using namespace std;
Registrar::Registrar() {
    filec = 1;
    entryTime = 0;
    medianArray = 0;
    idArray = 0;
    timeAtWindow = 0;
    stuClock = 0;
    openWindows = 0;
    totalStudents = 0;
    windowArray = NULL;
    idleArray = NULL;
    medianArrary = NULL;
}
Registrar::~Registrar() {
    if (windowArray != NULL){
      delete[] windowArray;
    }
    if (idleArray != NULL){
      delete[] idleArray;
    }
    if (medianArrary != NULL){
      delete[] medianArrary;
    }
}
//funtion that imports file
bool Registrar::importFile(string file) {
    string line;
    int lineNum = 1;
//input stream for file to be ran in console
    ifstream inputStream;
    inputStream.open(file.c_str());
    try {
        getline(inputStream, line);
//aoti retuns as int
//goes through file
        openWindows = atoi(line.c_str());
        windowArray = new StudentTime*[openWindows];
        for(int i = 0; i < openWindows; ++i) {
            StudentTime* student = new StudentTime();
            windowArray[i] = student;
        }
        lineNum++;
    }
//unable to read file catch
    catch(exception e) {
        cout << "ERROR" << endl;
        return false;
    }
//clock
    while(getline(inputStream, line)) {
        switch(filec) {
            case(1): {
                try {
                    entryTime = atoi(line.c_str());
                    filec++;
                    lineNum++;
                }
//error catch
                catch(exception e) {
                    cout << "ERROR" << endl;
                    return false;
                }
                break;
            }
//students waiting
            case(2): {
                try {
                    if(line != "") {
                        stuClock = atoi(line.c_str());

                        for(int i = 0; i < stuClock; ++i) {
                            getline(inputStream, line);
                            lineNum++;
                            try {
                                timeAtWindow = atoi(line.c_str());
                            }
                            catch(exception e) {
                                cout << "ERROR" << endl;
                                return false;
                            }
                            totalStudents++;
                            StudentTime* student = new StudentTime(timeAtWindow, entryTime);
                            studentQueue.enqueue(student);
                        }
                        filec--;
                    }
                }
//catch error
                catch(exception e) {
                    cout << "ERROR" << endl;
                    return false;
                }
                break;
            }
            default:
                break;
        }
    }
    return true;
}
//time
bool Registrar::clockTick(int t) {
    for(int i = 0; i < openWindows; ++i) {
        if(windowArray[i]->windowTime > 0) {
            windowArray[i]->windowTime--;
        }
        else {
            windowArray[i]->idleTime++;
        }
    }
    if(!studentQueue.isEmpty()) {
        ListNode<StudentTime*> *curr = studentQueue.front;

        while(curr != NULL) {
            if(curr->data->entryTime < t) {
                curr->data->waitTime += 1;
            }
            curr = curr->next;
        }
    }
    return true;
}
//calculates mean time
double Registrar::meanTime() {
    ListNode<int> *curr = waitingData.front;
    double meanWaitTime = 0;
    double sum = 0;
    double counter = 0;
    while(curr != NULL) {
        sum += curr->data;
        curr = curr->next;
        counter++;
    }
    if(counter == 0) {
        return 0;
    }
    meanWaitTime = sum / counter;
    return meanWaitTime;
}
//calculates medican time
double Registrar::medianTime() {
    ListNode<int> *curr = waitingData.front;

    double medianWaitTime = 0;
    medianArray = 0;

    while(curr != NULL) {
        curr = curr->next;
        medianArray++;
    }

    if(medianArray == 0) {
        return 0;
    }
    else {
        medianArrary = new int[medianArray];
        curr = waitingData.front;

        for(int i = 0; i < medianArray; ++i) {
            medianArrary[i] = curr->data;
            curr = curr->next;
        }
        if(medianArray == 1) {
            return medianArrary[0];
        }
//if the number is odd
        else if(medianArray % 2 == 1) {
            double d = 0;
            int o = 0;

            o = (medianArray/2);
            d = medianArrary[o];

            return d;
        }
        else {
            double d = 0;
            int i = 0;
            int n = 0;

            i = medianArray/2;
            n = (medianArray/2) + 1;

            if(medianArrary[n] == 0) {
                return 0;
            }

            d = double(medianArrary[i])/double(medianArrary[n]);

            return d;
        }
    }
}
//calculates longest time
int Registrar::longestTime() {
    if(medianArray == 0) {
        return 0;
    }
    else {
        return medianArrary[medianArray - 1];
    }
}
//calculates time over ten minutes
int Registrar::overTime() {
    if(medianArray == 0) {
        return 0;
    }
    else {
        int hold = 0;

        for(int i = 0; i < medianArray; ++i) {
            if(medianArrary[i] > 10) {
                ++hold;
            }
        }
        return hold;
    }
}
//calculates mean idle time
double Registrar::meanIdleTime() {
    ListNode<int> *curr = idleData.front;

    double mnIdle = 0;
    double sum = 0;
    double counter = 0;

    while(curr != NULL) {
        sum += curr->data;
        curr = curr->next;

        counter++;
    }

    if(counter == 0) {
        return 0;
    }

    mnIdle = sum / counter;
    return mnIdle;
}
//calculates longest idle time
int Registrar::longestIdleTime() {
    ListNode<int> *curr = idleData.front;

    idArray = 0;

    while(curr != NULL) {
        curr = curr->next;
        idArray++;
    }

    idleArray = new int[idArray];

    curr = idleData.front;

    for(int i = 0; i < idArray; ++i) {
        idleArray[i] = curr->data;
        curr = curr->next;
    }

    sort(idleArray, idleArray + idArray);

    return(idleArray[idArray - 1
      ]);
}
//calculates idle time over five minutes
int Registrar::idleOverTime() {
    int hold = 0;

    for(int i = 0; i < idArray; ++i) {
        if(idleArray[i] > 5) {
            ++hold;
        }
    }

    return hold;
}
