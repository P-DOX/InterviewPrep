#include "Logger.h"
#include <iostream>
#include <string>
#include <thread>
using namespace std;

void user1Log(){
    Logger* obj1 = Logger :: getInstance();
    obj1->printLog("obj1 log");
}

void user2Log(){
    Logger* obj2 = Logger :: getInstance();
    obj2->printLog("obj2 log");
}

int main(){
    thread t1(user1Log);
    thread t2(user2Log);
    t1.join();
    t2.join();
    
}