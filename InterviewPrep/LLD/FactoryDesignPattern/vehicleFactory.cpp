#include "vehicleFactory.h"
#include "string"
using namespace std;

Vehicle* VehicleFactory :: getVehicle(string type){
    Vehicle* veh;
        if(type == "car")
            veh = new Car("Car", "Audi");
        else if(type == "bike")
            veh = new Bike("Bike", "Ducati");

    return veh;
}

