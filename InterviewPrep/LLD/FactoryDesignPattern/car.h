#ifndef car_h
#define car_h

#include "string"
#include "vehicle.h"
using namespace std;

class Car : public Vehicle{
    string brand;
    public:
        Car(string vehicleType, string brand);
        void createVehicle();
};

#endif