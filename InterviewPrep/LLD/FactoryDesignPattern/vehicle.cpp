#include "vehicle.h"
#include "string"
#include "iostream"
using namespace std;

Vehicle::Vehicle (string vehicleType) {
    this->vehicleType = vehicleType;
    cout<<"VehicleType "<<this->vehicleType<<" initialised\n";
}

// int main()
// {

// }