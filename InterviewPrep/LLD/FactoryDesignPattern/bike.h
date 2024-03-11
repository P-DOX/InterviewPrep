#ifndef bike_h
#define bike_h

#include "string"
#include "vehicle.h"
using namespace std;

class Bike : public Vehicle{
    string brand;
    public:
        Bike(string vehicleType, string brand);
        void createVehicle();
};

#endif