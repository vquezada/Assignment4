#include <iostream>
#include "StudentTime.h"
using namespace std;
StudentTime::StudentTime() {
    entryTime = 0;
    windowTime = 0;
    waitTime = 0;
    idleTime = 0;
}
StudentTime::StudentTime(int w, int e) {
    entryTime = e;
    windowTime = w;
    waitTime = 0;
    idleTime = 0;
}
StudentTime::~StudentTime() {
}
