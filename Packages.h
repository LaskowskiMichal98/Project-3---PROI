//
// Created by Michał Laskowski on 06/01/2019.
//

#ifndef DELIVERY_COMPANY_PACKAGES_H
#define DELIVERY_COMPANY_PACKAGES_H
using namespace std;
#include <string>

int randomNumber(int, int);
class Base;

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

};

class Package {
private:
    int numOfPackage;
    int size;
    int weight;
    Client *destination;
public:
    Package(int num, Client *delivery) {
        this->numOfPackage = num;
        this->destination = delivery;
        size = randomNumber(1, 10);
        this->weight = this->size * 100;
    }
};




#endif //DELIVERY_COMPANY_PACKAGES_H
