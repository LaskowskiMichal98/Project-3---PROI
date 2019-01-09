//
// Created by Michał Laskowski on 06/01/2019.
//
//@TODO sprawdzanie bankrupctwa przy uzyciu wyjatkow
//@TODO wszystkie couty tez do pliku
#include "Base.h"

MainBase* CreateChain(){
    MainBase* Center = new MainBase;
    Center->AddNewBase("Warszawa",140);
    Center->AddNewBase("Krakow",250);
    Center->AddNewBase("Gdansk",340);
    Center->AddNewBase("Wroclaw",280);
    Center->getSubBases()[0]->AddClient("KPMG",15);
    Center->getSubBases()[0]->AddClient("RRCustoms",50);
    Center->getSubBases()[0]->AddClient("Crucial",45);
    Center->getSubBases()[0]->AddClient("BlackRedWhite",30);
    Center->getSubBases()[0]->AddClient("Vileda",25);
    Center->getSubBases()[0]->AddNewBus();
    Center->getSubBases()[0]->AddNewTruck();
    Center->getSubBases()[1]->AddClient("Sony",20);
    Center->getSubBases()[1]->AddClient("PWN",10);
    Center->getSubBases()[1]->AddClient("Debica",50);
    Center->getSubBases()[1]->AddClient("CENTRA",30);
    Center->getSubBases()[1]->AddClient("Novox",25);
    Center->getSubBases()[1]->AddNewBus();
    Center->getSubBases()[1]->AddNewTruck();
    Center->getSubBases()[2]->AddClient("Behringer",30);
    Center->getSubBases()[2]->AddClient("Makita",15);
    Center->getSubBases()[2]->AddClient("Karcher",20);
    Center->getSubBases()[2]->AddClient("Canon",50);
    Center->getSubBases()[2]->AddClient("Garmin",40);
    Center->getSubBases()[2]->AddNewBus();
    Center->getSubBases()[2]->AddNewTruck();
    Center->getSubBases()[3]->AddClient("Casio",20);
    Center->getSubBases()[3]->AddClient("Lavazza",45);
    Center->getSubBases()[3]->AddClient("Adata",30);
    Center->getSubBases()[3]->AddClient("Sharp",50);
    Center->getSubBases()[3]->AddClient("Philips",10);
    Center->getSubBases()[3]->AddNewBus();
    Center->getSubBases()[3]->AddNewTruck();
    return Center;
}

void MainBase::AddNewBase(string name, int dist) {
    Base* newBase = new Base(name,dist,this);
    this->SubBases.push_back(newBase);
}

void Base::AddClient(string name,int dist){
    Client* newClient = new Client(name,dist,this);
    this->Clients.push_back(newClient);
}

Package* MainBase::CreateNewPackage(int num) {
    int branches = this->getSubBases().size();
    int branch1 = randomNumber(0,branches);
    int branch2 = randomNumber(0,branches);
    int senders = this->getSubBases()[branch1]->getClients().size();
    int receivers= this->getSubBases()[branch1]->getClients().size();
    int senderNum;
    int receiverNum;

    do{
        senderNum = randomNumber(0,senders);
        receiverNum = randomNumber(0,receivers);
    }while(branch1==branch2 && senderNum==receiverNum);

    Client* sender = this->getSubBases()[branch1]->getClients()[senderNum];
    Client* receiver = this->getSubBases()[branch2]->getClients()[receiverNum];
    Package* newPackage = new Package(num);
    newPackage->setSender(sender);
    newPackage->setReceiver(receiver);
    newPackage->setNumOfPackage(num);

    cout << "Paczka numer " << num << " w kierunku " << this->getSubBases()[branch2]->getClients()[receiverNum]->getClientName() <<
    " oczekuje w firmie " << this->getSubBases()[branch1]->getClients()[senderNum]->getClientName() << "." << endl;

    return newPackage;
}

void Base::AddNewBus() {
    Car* bus = new Car(this, "Bus");
    this->Bus.push_back(bus);
}

void Base::AddNewTruck(){
    Car* bus = new Car(this, "TIR");
    this->Truck.push_back(bus);
}

void Package::CollectPackage(MainBase * Center) {
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
        Center->SetBudget(Center->getSubBases()[tempBase]->getBus()[0]->NeedToTankUp(Center->getSubBases()[tempBase]->getClients()[tempSender]->getDistance()));
    }
    this->setLocation(Center->getSubBases()[tempBase]);
    Center->getSubBases()[tempSender]->getPackages().push_back(this);
}

void Package::checkPackageDestination(MainBase* Center){
    Base* BaseDest;
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        for (int j = 0; j < Center->getSubBases()[i]->getClients().size(); ++j) {
            if(this->receiver == Center->getSubBases()[i]->getClients()[j]){
                BaseDest = Center->getSubBases()[i];
            }
        }
    }

    if(this->Location == BaseDest){
        this->DeliverPackage();
    }

    else
        this->getLocation()->getTruck()[0]->placePackageInTruck(this);
}

void Package::DeliverPackage() {
    for (int i = 0; i < 2; ++i) {
        this->Location->getBus()[0]->NeedToTankUp(this->getReceiver()->getDistance());
    }
    this->Location->getPackages().clear();

    cout << "Paczka numer " << this->getNumOfPackage() << " zostala dostarczona do firmy " << this->receiver->getClientName() << endl;
}

void Car::placePackageInTruck(Package* package) {
    this->LoadingSpace.push_back(package);
    package->getLocation()->getPackages().pop_back();
    this->loadATM+=package->getWeight();
    this->storageATM+=package->getSize();
}

void Base::SendTruckToCenter() {
    this->getTruck()[0]->NeedToTankUp(this->getDistanceToBase());
    for (int i = 0; i < this->getTruck()[0]->getLoadingSpace().size(); ++i) {
        this->getCenter()->getPackages().push_back(this->getTruck()[0]->getLoadingSpace()[i]);
    }

    vector <int> toBeCollected;
    for (int j = 0; j < this->getCenter()->getPackages().size(); ++j) {
        if(this->getCenter()->getPackages()[j]->getDirection() == this){
            this->getTruck()[0]->getLoadingSpace().push_back(this->getCenter()->getPackages()[j]);
            toBeCollected.push_back(j);
        }
    }
    vector<Package*>::iterator it;

    for (int k = toBeCollected.size()-1; k >= 0; --k) {
        it = this->Center->getPackages().begin();
        this->getCenter()->getPackages().erase(it + toBeCollected[k]);
    }

    while(!this->getTruck()[0]->getLoadingSpace().empty()){
        this->getPackages().push_back(this->getTruck()[0]->getLoadingSpace().back());
        this->getTruck()[0]->getLoadingSpace().pop_back();
    }
    this->getTruck()[0]->setLoadATM(0);
    this->getTruck()[0]->setStorageATM(0);

    for (int l = this->getPackages().size(); l >=0 ; --l) {
        this->getPackages()[l]->DeliverPackage();
    }
}

void TakeCareOfPackage(MainBase* Center, int repeatsDone, int repeats){
    Package* newPackage;
    newPackage = Center->CreateNewPackage(repeatsDone);
    newPackage->CollectPackage(Center);
    newPackage->checkPackageDestination(Center);
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        if(Center->getSubBases()[i]->getTruck()[0]->getLoadATM() > 21000 || Center->getSubBases()[i]->getTruck()[0]->getStorageATM()>63
           || repeatsDone == repeats-1){
            Center->getSubBases()[i]->SendTruckToCenter();
        }
    }
}
}