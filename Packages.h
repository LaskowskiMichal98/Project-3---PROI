//
// Created by Michał Laskowski on 06/01/2019.
//

#ifndef DELIVERY_COMPANY_PACKAGES_H
#define DELIVERY_COMPANY_PACKAGES_H
using namespace std;
#include <string>

int randomNumber(int, int);
class Base;
class MainBase;

class Client{
private:
    string clientName;
    int distance;
    Base* contractor;
public:
    Client(string name,int dist,Base* base){
        this->clientName=name;
        this->distance=dist;
        this->contractor=base;
    }

    string getClientName(){
        return this->clientName;
    }
    int getDistance(){
        return this->distance;
    }

};

class Package {
private:
    Base* Location;
    int price;
    int numOfPackage;
    int size;
    int weight;
    string sender;
    string receiver;
public:
    Package(int num) {
        this->numOfPackage = num;
        size = randomNumber(1, 6);
        this->weight = this->size * 100;
        this->price=this->size*10;
    }
    void setSender(string sender){
        this->sender=sender;
    }
    void setReceiver(string receiver){
        this->receiver=receiver;
    }
    void setLocation(Base* location){
        this->Location=location;
    }

    void CollectPackage(MainBase*);
    void checkPackageDestination(MainBase*);
};




#endif //DELIVERY_COMPANY_PACKAGES_H
