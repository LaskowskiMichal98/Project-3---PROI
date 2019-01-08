//
// Created by Michał Laskowski on 06/01/2019.
//


#ifndef DELIVERY_COMPANY_CARS_H
#define DELIVERY_COMPANY_CARS_H


#include <vector>
#include <string>
using namespace std;

class Base;

class Car {
private:
    string Type;
    Base* owner;
    int storage;
    int maximumLoad;
    double fuelTankCapacity;
    double fuelEconomy;
    double fuelLeft;
public:
    Car(Base* own, string type){
        this->owner=own;
        if (type == "Bus") {
                this->Type=type;
                this->maximumLoad = 1500;
                this->fuelTankCapacity = 80;
                this->storage = 5;
                this->fuelEconomy = 3/25;
                this->fuelLeft = this->fuelTankCapacity;
        }
        else if(type == "TIR"){
                this->Type=type;
                this->maximumLoad = 24000;
                this->fuelTankCapacity = 1300;
                this->storage = 70;
                this->fuelEconomy = 1/2;
                this->fuelLeft = this->fuelTankCapacity;
        }
        }

    int tankUp();
    double NeedToTankUp(int);
};




#endif //DELIVERY_COMPANY_CARS_H
