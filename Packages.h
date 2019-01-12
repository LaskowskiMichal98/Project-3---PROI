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
    Base* Direction;
    int price;
    int numOfPackage;
    int size;
    int weight;
    Client* sender;
    Client* receiver;
public:
    Package(int num) {
        this->numOfPackage = num;
        size = randomNumber(1, 10);
        this->weight = this->size * 500;
        this->price=this->size*10;
    }
    void setSender(Client* sender){
        this->sender=sender;
    }
    void setReceiver(Client* receiver){
        this->receiver=receiver;
    }
    void setLocation(Base* location){
        this->Location=location;
    }
    void setNumOfPackage(int num){
        this->numOfPackage = num;
    }
    void setDirection(Base* destination){
        this->Direction = destination;
    }
    Client* getReceiver(){
        return this->receiver;
    }
    int getNumOfPackage(){
        return this->numOfPackage;
    }
    Base* getLocation(){
        return this->Location;
    }
    Base* getDirection(){
        return this->Direction;
    }
    int getSize(){
        return this->size;
    }
    int getWeight(){
        return this->weight;
    }

    void CollectPackage(MainBase*);
    void checkPackageDestination(MainBase*);
    void DeliverPackage(int);
};




#endif //DELIVERY_COMPANY_PACKAGES_H
