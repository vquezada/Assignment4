#include <iostream>

using namespace std;

class StudentTime {
    private:
    public:
        StudentTime();
        StudentTime(int w, int e);
        ~StudentTime();
        int entryTime;
        int windowTime;
        int waitTime;
        int idleTime;
};
