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

