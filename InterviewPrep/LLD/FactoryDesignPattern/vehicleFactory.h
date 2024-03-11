#ifndef vehicleFactory_h
#define vehicleFactory_h

#include "bike.h"
#include "car.h"

class VehicleFactory {
    public : 
        static Vehicle* getVehicle(string type);
};

#endif