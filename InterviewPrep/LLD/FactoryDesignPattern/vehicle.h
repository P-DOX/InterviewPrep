#ifndef vehicle_h
#define vehicle_h

#include "string"
using namespace std;


class Vehicle {
    
    public:
        string vehicleType;
        Vehicle(string vehicleType);
        virtual void createVehicle() = 0;
};

#endif