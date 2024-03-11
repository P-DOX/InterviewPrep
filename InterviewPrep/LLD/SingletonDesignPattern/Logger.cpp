#include "Logger.h"
#include <iostream>
#include <string>
using namespace std;

Logger* Logger :: loggerInstance = NULL;
mutex Logger :: mtx;

Logger :: Logger() {
    cout<<"Object created \n";
}

Logger* Logger :: getInstance(){

    if(loggerInstance == nullptr){
        mtx.lock();
        if(loggerInstance == nullptr){
            loggerInstance = new Logger();
        }
        mtx.unlock();
    }
    
    return loggerInstance;
}

void Logger :: printLog(string msg){
    cout<<msg<<endl;
}