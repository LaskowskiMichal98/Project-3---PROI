//
// Created by Michał Laskowski on 06/01/2019.
//


#ifndef DELIVERY_COMPANY_CARS_H
#define DELIVERY_COMPANY_CARS_H

#include "Base.h"
#include "Packages.h"
#include <vector>
using namespace std;

class Car {
private:
    vector<Package> Load;
    Base* owner;
    int storage;
    int maximumLoad;
    int fuelTankCapacity;
    double fuelEconomy;
    int fuelLeft;
public:
    Car(int type,Base* own){
        this->owner=own;
        if(type==1){
            this->maximumLoad=24000;
            this->fuelTankCapacity=1300;
            this->fuelLeft=this->fuelTankCapacity;
            this->storage=70;
            this->fuelEconomy = 1/2;
        }
        else if(type==2){
            this->maximumLoad=1500;
            this->fuelTankCapacity=80;
            this->fuelLeft=this->fuelTankCapacity;
            this->storage=5;
            this->fuelEconomy = 3/25;
        }
    }
    int tankUp();
};



#endif //DELIVERY_COMPANY_CARS_H
