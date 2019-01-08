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
public:
    MainBase(string name = "Kutno", int startBudget = 0){
        this->City = name;
        this->budget= startBudget;
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
    bool checkBunkruptcy(){
        if(this->budget<0){
            return true;
        }
        return false;
    }

    void AddNewBase(string,int);
    Package CreateNewPackage(int);
};


class Base: public MainBase{
private:
    MainBase* Destination;
    vector<Client*> Clients;
    vector<Package> Packages;
    int DistanceToBase;
    vector<Car*> Bus;
    vector<Car*> Truck;

public:

    Base(string name,int dist,MainBase* dest) :MainBase(name){
        this->Destination = dest;
        this->DistanceToBase = dist;
    }
    vector<Client*> getClients(){
        return this->Clients;
    }
    vector<Package> getPackages(){
        return this -> Packages;
    }
    vector<Car*> getBus(){
        return this->Bus;
    }
    vector<Car*> getTruck(){
        return this->Truck;
    }

    void AddClient(string,int);
    void AddNewBus();
    void AddNewTruck();
};

MainBase* CreateChain();


#endif //DELIVERY_COMPANY_BASE_H
