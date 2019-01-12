//
// Created by Michał Laskowski on 06/01/2019.
//


#ifndef DELIVERY_COMPANY_CARS_H
#define DELIVERY_COMPANY_CARS_H


#include <vector>
#include <string>

using namespace std;
class Package;
class Base;

class Car {
private:
    vector<Package*> LoadingSpace;
    string Type;
    Base* owner;
    int storage;
    int storageATM;
    int loadATM;
    int maximumLoad;
    double fuelTankCapacity;
    double fuelEconomy;
    double fuelLeft;
public:
    Car(Base* own, string type){
        this->owner=own;
        vector<Package*>* tempLoadingSpace = new vector<Package*>;
        if (type == "Bus") {
                this->LoadingSpace = *tempLoadingSpace;
                this->Type=type;
                this->maximumLoad = 2000;
                this->fuelTankCapacity = 80;
                this->storage = 5;
                this->fuelEconomy = 3/25;
                this->fuelLeft = this->fuelTankCapacity;
        }
        else if(type == "TIR"){
                this->LoadingSpace = *tempLoadingSpace;
                this->Type=type;
                this->maximumLoad = 24000;
                this->fuelTankCapacity = 1300;
                this->storage = 70;
                this->fuelEconomy = 1/2;
                this->fuelLeft = this->fuelTankCapacity;
                this->storageATM = 0;
                this->loadATM = 0;
        }
        }

    vector<Package*> getLoadingSpace(){
            return this->LoadingSpace;
    }
    void setFuelLeft(double fuel){
        this->fuelLeft = fuel;
    }
    void setStorageATM(int temp){
            this->storageATM=temp;
    }
    void setLoadATM(int temp){
            this->loadATM=temp;
    }
    int getLoadATM(){
            return this->loadATM;
    }
    int getStorageATM(){
            return this->storageATM;
    }
    string getType(){
            return this->Type;
    }
    Base* getOwner(){
            return this->owner;
    }
    void AddLoadingSpace(Package* package){
        this->LoadingSpace.push_back(package);
    }
    void PopLoadingSpace(){
        this->LoadingSpace.pop_back();
    }

    double NeedToTankUp(int);
    void placePackageInTruck(Package*);
};




#endif //DELIVERY_COMPANY_CARS_H
