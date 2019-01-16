//
// Created by Michał Laskowski on 06/01/2019.
//

#include "Base.h"
#include "Cars.h"
#include "Packages.h"

void MainBase::AddNewBase(string name, int dist) {
    Base* newBase = new Base(name,dist,this);
    this->SubBases.push_back(newBase);
}

void Base::AddClient(string name,int dist){
    Client* newClient = new Client(name,dist);
    this->Clients.push_back(newClient);
}

void Base::AddNewBus() {
    Car* bus = new Car(this, "Bus");
    this->Bus.push_back(bus);
}

void Base::AddNewTruck(){
    Car* bus = new Car(this, "TIR");
    this->Truck.push_back(bus);
}

void Base::SendTruckToCenter(fstream* processFile) {
    this->getCenter()->SetBudget(this->getTruck()[0]->NeedToTankUp(this->getDistanceToBase(),processFile));
    cout << "TIR z bazy " << this->getCity() << " wyruszyl z ladunkiem do glownej bazy." << endl;
    *processFile << "TIR z bazy " << this->getCity() << " wyruszyl z ladunkiem do glownej bazy." << endl;
    while(!this->getTruck()[0]->getLoadingSpace().empty()){
        this->getCenter()->AddPackages(this->getTruck()[0]->getLoadingSpace().back());
        this->getTruck()[0]->PopLoadingSpace();
    }

    for (int j = 0; j < this->getCenter()->getPackages().size(); ++j) {
        if(this->getCenter()->getPackages()[j]->getDirection() == this){
            this->getTruck()[0]->AddLoadingSpace(this->getCenter()->getPackages()[j]);
            this->getCenter()->erasePackage(j);
        }
    }

    (this->getCenter()->SetBudget(this->getTruck()[0]->NeedToTankUp(this->getDistanceToBase(),processFile)));
    cout << "TIR wyruszyl z ladunkiem z bazy glownej do " << this->getCity() << endl;
    *processFile << "TIR wyruszyl z ladunkiem z bazy glownej do " << this->getCity() << endl;
        while(!this->getTruck()[0]->getLoadingSpace().empty()) {
            this->AddPackages(this->getTruck()[0]->getLoadingSpace().back());
            this->getTruck()[0]->PopLoadingSpace();
            this->getPackages()[this->getPackages().size() - 1]->DeliverPackage(processFile);
        }
        this->getTruck()[0]->setLoadATM(0);
        this->getTruck()[0]->setStorageATM(0);

}

Package* MainBase::CreateNewPackage(int num, fstream* processFile) {
    int branches = this->getSubBases().size();
    int branch1 = randomNumber(0,branches);
    int branch2;
    do {
        branch2 = randomNumber(0,branches);
    }while(branch1==branch2 && this->getSubBases()[branch2]->getClients().size()<2);

    int senderNum;
    int receiverNum;
    int senders = this->getSubBases()[branch1]->getClients().size();
    int receivers = this->getSubBases()[branch2]->getClients().size();
    do{
        senderNum = randomNumber(0,senders);
        if(this->getSubBases()[branch2]->getClients().size()==1){
            receiverNum=0;
        }
        else{
            receiverNum = randomNumber(0,receivers);
        }
    }while(branch1==branch2 && senderNum==receiverNum);

    Client* sender = this->getSubBases()[branch1]->getClients()[senderNum];
    Client* receiver = this->getSubBases()[branch2]->getClients()[receiverNum];
    Package* newPackage = new Package(num);
    this->AddPackageCollected();
    newPackage->setSender(sender);
    newPackage->setReceiver(receiver);
    newPackage->setDirection(this->getSubBases()[branch2]);

    cout << "Paczka numer " << num << " w kierunku " << this->getSubBases()[branch2]->getClients()[receiverNum]->getClientName() <<
         " oczekuje w firmie " << this->getSubBases()[branch1]->getClients()[senderNum]->getClientName() << "." << endl;
    *processFile << "Paczka numer " << num << " w kierunku " << this->getSubBases()[branch2]->getClients()[receiverNum]->getClientName() <<
                 " oczekuje w firmie " << this->getSubBases()[branch1]->getClients()[senderNum]->getClientName() << "." << endl;

    return newPackage;
}