#include "bike.h"
#include "iostream"
using namespace std;

Bike :: Bike(string vehicleType, string brand) : Vehicle(vehicleType) {
    this->brand = brand;
}

void Bike :: createVehicle() {
    cout<<"Creating Bike";
    cout<<"Accessing parent "<<this->vehicleType<<endl;
}