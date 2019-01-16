//
// Created by Michał Laskowski on 06/01/2019.
//

#include <iostream>
#include "Cars.h"
#include "Base.h"
#include "Packages.h"
using namespace std;

double Car::NeedToTankUp(int dist, fstream* processFile) {
    double tempFuel = this->fuelLeft;
    tempFuel -= dist*this->fuelEconomy;
    if(tempFuel<=0){
        this->fuelLeft = (this->fuelTankCapacity + tempFuel);
        cout << "Zatankowano " << this->getType() << " nalezacy do bazy " << this->getOwner()->getCity() << " za kwote " << this->fuelTankCapacity * 5 << " zl" << endl;
        *processFile << "Zatankowano " << this->getType() << " nalezacy do bazy " << this->getOwner()->getCity() << " za kwote " << this->fuelTankCapacity * 5 << " zl" << endl;
        return -(this->fuelTankCapacity * 5);
    }
    else {
        this->fuelLeft = tempFuel;
        return 0;
    }
}

void Car::placePackageInTruck(Package* package) {
    this->LoadingSpace.push_back(package);
    package->getLocation()->PopPackage();
    this->loadATM+=package->getWeight();
    this->storageATM+=package->getSize();
}

