//
// Created by Michał Laskowski on 06/01/2019.
//
#ifndef DELIVERY_COMPANY_BASE_H
#define DELIVERY_COMPANY_BASE_H
#include <string>
#include <vector>
#include <iostream>
#include "Packages.h"
using namespace std;

class Base;

class MainBase {
private:
    int budget;
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
    void AddNewBase(string,int);

    string getCity(){
        return this->City;
    }
};


class Base: public MainBase{
private:
    MainBase* Destination;
    vector<Client*> Clients;
    int DistanceToBase;

public:

    Base(string name,int dist,MainBase* dest) :MainBase(name){
        this->Destination = dest;
        this->DistanceToBase = dist;
    }
    vector<Client*> getClients(){
        return this->Clients;
    }

    void AddClient(string,int);
};

MainBase* CreateChain();

#endif //DELIVERY_COMPANY_BASE_H
