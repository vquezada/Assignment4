#include <iostream>
#include <string>
#include "StudentTime.h"
#include "StudentQueue.h"
using namespace std;
class Registrar {
    private:
        int filec;
        int entryTime;
        int timeAtWindow;
        int stuClock;
        int medianArray;
        int idArray;
    public:
        Registrar();
        ~Registrar();
        bool importFile(string file);
        bool clockTick(int t);
//calculation variables
        double meanTime();
        double medianTime();
        int longestTime();
        int overTime();
//calculations
        double meanIdleTime();
        int longestIdleTime();
        int idleOverTime();
//students in windows
        StudentTime* *windowArray;
//students waiting
        StudentQueue<StudentTime*> studentQueue;
        StudentQueue<int> waitingData;
        StudentQueue<int> idleData;
        int *medianArrary;
        int *idleArray;
        int openWindows;
        int totalStudents;
};
