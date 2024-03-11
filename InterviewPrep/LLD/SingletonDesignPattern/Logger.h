#ifndef logger_h
#define logger_h
#include <string>
#include <mutex>

using namespace std;

class Logger {
    Logger();
    static Logger* loggerInstance; 
    static mutex mtx;
    public:
    static Logger* getInstance();
    void printLog(string str);
};

#endif