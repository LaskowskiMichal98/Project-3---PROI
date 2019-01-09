//
// Created by Michał Laskowski on 06/01/2019.
//

#include "Cars.h"

int Car::tankUp() {
    int cost;
    cost=(this->fuelTankCapacity - this->fuelLeft)*5;
    this->fuelLeft=this->fuelTankCapacity;

    return cost;
}

double Car::NeedToTankUp(int dist) {
    double tempFuel = this->fuelLeft - dist*this->fuelEconomy;
    if(tempFuel<=0){
        this->fuelLeft = (this->fuelTankCapacity + tempFuel);
        return (this->fuelLeft * 5);
    }
    return 0;
}


