#include "iostream"
#include "vehicleFactory.h"
using namespace std;

int main(){
    string type;

    while(true){
        cout<<"Vehicle type : ";
        cin>>type;

        Vehicle* veh = VehicleFactory::getVehicle(type);
        veh->createVehicle();
        cout<<endl;
    }
}
