//
// Created by Michał Laskowski on 06/01/2019.
//
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
    int receivers= this->getSubBases()[branch2]->getClients().size();
    int senderNum;
    int receiverNum;

    do{
        senderNum = randomNumber(0,senders);
        receiverNum = randomNumber(0,receivers);
    }while(branch1==branch2 && senderNum==receiverNum);

    Client* sender = this->getSubBases()[branch1]->getClients()[senderNum];
    Client* receiver = this->getSubBases()[branch2]->getClients()[receiverNum];
    Package* newPackage = new Package(num);
    this->AddPackageCollected();
    newPackage->setSender(sender);
    newPackage->setReceiver(receiver);
    newPackage->setDirection(this->getSubBases()[branch2]);

//    cout << "Paczka numer " << num << " w kierunku " << this->getSubBases()[branch2]->getClients()[receiverNum]->getClientName() <<
//    " oczekuje w firmie " << this->getSubBases()[branch1]->getClients()[senderNum]->getClientName() << "." << endl;

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
    Center->getSubBases()[tempBase]->AddPackages(this);
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
        this->DeliverPackage(0);
    }

    else
        this->getLocation()->getTruck()[0]->placePackageInTruck(this);
}

void Package::DeliverPackage(int temp) {
    for (int i = 0; i < 2; ++i) {
        this->Location->getBus()[0]->NeedToTankUp(this->getReceiver()->getDistance());
    }
    this->Location->ClearPackages();
    //cout << "Paczka numer " << this->getNumOfPackage() << " zostala dostarczona do firmy " << this->receiver->getClientName() << endl;
    this->getLocation()->getCenter()->AddPackagesDelivered();

}

void Car::placePackageInTruck(Package* package) {
    this->LoadingSpace.push_back(package);
    package->getLocation()->PopPackage();
    this->loadATM+=package->getWeight();
    this->storageATM+=package->getSize();
}

void Base::SendTruckToCenter() {
    this->getTruck()[0]->NeedToTankUp(this->getDistanceToBase());
//    cout << "TIR z bazy " << this->getCity() << " wyruszyl z ladunkiem do glownej bazy." << endl;

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

    this->getTruck()[0]->NeedToTankUp(this->getDistanceToBase());
    cout << "TIR wyruszyl z ladunkiem z bazy glownej do " << this->getCity() << endl;

        while(!this->getTruck()[0]->getLoadingSpace().empty()) {
            this->AddPackages(this->getTruck()[0]->getLoadingSpace().back());
            this->getTruck()[0]->PopLoadingSpace();
            this->getPackages()[this->getPackages().size() - 1]->DeliverPackage(1);
        }
        this->getTruck()[0]->setLoadATM(0);
        this->getTruck()[0]->setStorageATM(0);

}

void TakeCareOfPackage(MainBase* Center, int repeatsDone){
    Package* newPackage;
    newPackage = Center->CreateNewPackage(repeatsDone);
    newPackage->CollectPackage(Center);
    newPackage->checkPackageDestination(Center);
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        if(Center->getSubBases()[i]->getTruck()[0]->getLoadATM() > 21000 || Center->getSubBases()[i]->getTruck()[0]->getStorageATM()>63){
            Center->getSubBases()[i]->SendTruckToCenter();
        }
    }
}

double Car::NeedToTankUp(int dist) {
    double tempFuel = this->fuelLeft - dist*this->fuelEconomy;
    if(tempFuel<=0){
        this->setFuelLeft(this->fuelTankCapacity + tempFuel);
        cout << "Zatankowano " << this->getType() << " nalezacy do bazy " << this->getOwner()->getCity() << " za kwote " << this->fuelLeft * 5 << " zl" << endl;
        return (this->fuelLeft * 5);

    }
    this->setFuelLeft(tempFuel);
    return 0;
}