//
// Created by Michał Laskowski on 06/01/2019.
//

#include "Packages.h"
#include "Cars.h"
#include "Base.h"

using namespace std;

void Package::DeliverPackage(fstream* processFile) {
    for (int i = 0; i < 2; ++i) {
        this->Location->getCenter()->SetBudget(this->Location->getBus()[0]->NeedToTankUp(this->getReceiver()->getDistance(),processFile));
    }
    this->Location->ClearPackages();
    cout << "Paczka numer " << this->getNumOfPackage() << " zostala dostarczona do firmy " << this->receiver->getClientName() << endl;
    *processFile << "Paczka numer " << this->getNumOfPackage() << " zostala dostarczona do firmy " << this->receiver->getClientName() << endl;
    this->getLocation()->getCenter()->AddPackagesDelivered();
}

void Package::checkPackageDestination(MainBase* Center,fstream* processFile){
    Base* BaseDest;
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        for (int j = 0; j < Center->getSubBases()[i]->getClients().size(); ++j) {
            if(this->receiver == Center->getSubBases()[i]->getClients()[j]){
                BaseDest = Center->getSubBases()[i];
            }
        }
    }

    if(this->Location == BaseDest){
        this->DeliverPackage(processFile);
    }

    else
        this->getLocation()->getTruck()[0]->placePackageInTruck(this);
}

void Package::CollectPackage(MainBase * Center,fstream* processFile) {
    int tempBase = 0;
    int tempSender = 0;
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        for (int j = 0; j < Center->getSubBases()[i]->getClients().size(); ++j) {
            if(this->sender->getClientName() == Center->getSubBases()[i]->getClients()[j]->getClientName()){
                tempBase = i;
                tempSender = j;
            }
        }
    }

    Center->SetBudget(this->price);
    for (int k = 0; k < 2; ++k) {
        Center->SetBudget(Center->getSubBases()[tempBase]->getBus()[0]->NeedToTankUp(Center->getSubBases()[tempBase]->getClients()[tempSender]->getDistance(),processFile));
    }
    this->setLocation(Center->getSubBases()[tempBase]);
    Center->getSubBases()[tempBase]->AddPackages(this);
}