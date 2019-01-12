//
// Created by Michał Laskowski on 06/01/2019.
//
#ifndef DELIVERY_COMPANY_BASE_H
#define DELIVERY_COMPANY_BASE_H
#include <string>
#include <vector>
#include <iostream>
#include "Cars.h"
#include "Packages.h"
using namespace std;

class Base;
class Car;

class MainBase {
private:
    double budget;
    string City;
    vector<Base*> SubBases;
    vector<Package*> Packages;
    int PackagesCollected;
    int PackagesDelivered;
public:
    MainBase(string name = "Lodz", int startBudget = 0){
        vector<Base*>* tempBases = new vector<Base*>;
        this->SubBases=*tempBases;
        vector<Package*>* tempPackages = new vector<Package*>;
        this->Packages = *tempPackages;
        this->City = name;
        this->budget= startBudget;
        this->PackagesCollected = 0;
        this->PackagesDelivered = 0;
    }
    vector<Base*> getSubBases(){
        return this->SubBases;
    }
    string getCity(){
        return this->City;
    }
    void SetBudget(double money){
        this->budget += money;
    }
    vector<Package*> getPackages(){
        return this -> Packages;
    }
    void AddPackages(Package* package){
        this->Packages.push_back(package);
    }
    void PopPackage(){
        this->Packages.pop_back();
    }
    void ClearPackages(){
        this->Packages.clear();
    }
    void erasePackage(int temp){
        this->Packages.erase(this->Packages.begin() + temp);
    }
    void AddPackageCollected(){
        this->PackagesCollected++;
    }
    void AddPackagesDelivered(){
        this->PackagesDelivered++;
    }
    int getPackagesDelivered(){
        return this->PackagesDelivered;
    }
    int getPackagesCollected(){
        return this->PackagesCollected;
    }
    void AddNewBase(string,int);
    Package* CreateNewPackage(int);
};


class Base: public MainBase{
private:
    MainBase* Center;
    vector<Client*> Clients;
    int DistanceToBase;
    vector<Car*> Bus;
    vector<Car*> Truck;

public:

    Base(string name,int dist,MainBase* dest) :MainBase(name){
        this->Center = dest;
        this->DistanceToBase = dist;
        vector<Car*>* tempBus = new vector<Car*>;
        this->Bus = *tempBus;
        vector <Car*>* tempTIR = new vector<Car*>;
        this->Truck = *tempTIR;
        vector <Client*>* tempClients = new vector<Client*>;
        this->Clients = *tempClients;
    }
    vector<Client*> getClients(){
        return this->Clients;
    }

    vector<Car*> getBus(){
        return this->Bus;
    }
    vector<Car*> getTruck(){
        return this->Truck;
    }
    int getDistanceToBase(){
        return this->DistanceToBase;
    }
    MainBase* getCenter(){
        return this->Center;
    }

    void AddClient(string,int);
    void AddNewBus();
    void AddNewTruck();
    void SendTruckToCenter();
};

MainBase* CreateChain();
void TakeCareOfPackage(MainBase*,int);


#endif //DELIVERY_COMPANY_BASE_H
