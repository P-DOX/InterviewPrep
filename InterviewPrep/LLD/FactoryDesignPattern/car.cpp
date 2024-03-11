#include "car.h"
#include "iostream"
using namespace std;

Car :: Car(string vehicleType, string brand) : Vehicle(vehicleType) {
    this->brand = brand;
}


void Car :: createVehicle() {
    cout<<"Creating Car";
}