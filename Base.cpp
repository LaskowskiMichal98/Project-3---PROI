//
// Created by Michał Laskowski on 06/01/2019.
//

#include "Base.h"
#define CLEAR "clear"

int menu(MainBase* Center,fstream* processFile,fstream* reportFile){
    system(CLEAR);
    cout << "---------------------------------------------------------" << endl;
    cout << "1. Dodaj nowa baze" << endl << endl;
    cout << "2. Dodaj nowego klienta" << endl << endl;
    cout << "3. Symuluj dzialanie firmy" << endl << endl;
    cout << "0. Wyjdz" << endl;
    cout << "---------------------------------------------------------" << endl << endl;
    string temp;
    string error = "Zla opcja, wcisnij enter aby kontynuowac";
    cout << "Opcja: ";
    getline(cin,temp);
    if(temp[0]!='0' && temp[0]!='1'&& temp[0]!='2' && temp[0]!='3'){
        throw error;
    }

    switch(temp[0]){
        case '1' : AddNewBaseManually(Center,processFile,reportFile); break;
        case '2' : AddNewClient(Center,processFile,reportFile); break;
        case '3' : Simulate(Center,processFile,reportFile); break;
        case '0' : return 0;
    }
    return 0;
}

void AddNewClient(MainBase* Center,fstream* processFile,fstream* reportFile){
    system(CLEAR);
    cout << "---------------------------------------------------------" << endl;
    cout << "Wybierz baze przy ktorej chcesz utworzyc nowego klienta:" << endl;
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        cout << i << ". " << Center->getSubBases()[i]->getCity() << endl;
    }
    cout << "---------------------------------------------------------" << endl;
    string temp;
    int num;
    cout << "Wybieram: ";
    cin >> num;
    getline(cin,temp);
    system(CLEAR);
    cout << "Podaj nazwe firmy: ";
    string name;
    getline(cin,name);
    cout << endl << "Podaj odleglosc od bazy: ";
    int distance;
    cin >> distance;

    Center->getSubBases()[num]->AddClient(name,distance);
    cout << endl << "Utworzono nowego klienta." << endl;


    cout << endl << "Wcisnij enter aby kontynuowac";
    getline(cin,temp);
    getline(cin,temp);

    menu(Center,processFile,reportFile);
}

void AddNewBaseManually(MainBase* Center,fstream* processFile,fstream* reportFile){
    string city;
    int distance;
    system(CLEAR);
    cout << "Podaj miasto, w ktorym ma zostac utworzona baza: " ;
    getline(cin,city);
    cout << endl << "Podaj odleglosc do bazy glownej (w Lodzi) : " ;
    cin >> distance;

    Center->AddNewBase(city,distance);
    Center->getSubBases()[Center->getSubBases().size()-1]->AddNewBus();
    Center->getSubBases()[Center->getSubBases().size()-1]->AddNewTruck();
    cout << "Utworzono nowa baze w " << city << endl;

    string temp;
    cout << endl << "Wcisnij enter aby kontynuowac";
    getline(cin,temp);
    getline(cin,temp);

    menu(Center,processFile,reportFile);
}

void Simulate(MainBase* Center,fstream* processFile,fstream* reportFile){
    system(CLEAR);
    int repeats;
    if(!checkClients(Center)){
        cout << "Do ktorejs z baz nie ma przylaczonych klientow." << endl;
        string temp;
        cout << endl << "Wcisnij enter aby kontynuowac";
        getline(cin,temp);
        menu(Center,processFile,reportFile);
    }
    cout << "Podaj liczbe paczek w symulacji : ";
    cin >> repeats;
    int repeatsDone = 0;

    while (repeatsDone != repeats) {
        repeatsDone++;
        TakeCareOfPackage(Center, repeatsDone, processFile);
    }

    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        if(!Center->getSubBases()[i]->getTruck()[0]->getLoadingSpace().empty()){
            Center->getSubBases()[i]->SendTruckToCenter(processFile);
        }
    }

    while(Center->getPackages().size()){
        Center->getPackages()[0]->getDirection()->SendTruckToCenter(processFile);
    }

    cout << "Paczki odebrane: " << Center->getPackagesCollected() << endl;
    cout << "Paczki dostarczone: " << Center->getPackagesDelivered() << endl;
    cout << "Budzet: " << Center->getBudget() << endl;
    *reportFile << "Paczki odebrane: " << Center->getPackagesCollected() << endl;
    *reportFile << "Paczki dostarczone: " << Center->getPackagesDelivered() << endl;
    *reportFile << "Budzet: " << Center->getBudget() << endl;
    string temp;
    cout << endl << "Wcisnij enter aby kontynuowac";
    getline(cin,temp);
    getline(cin,temp);

    menu(Center,processFile,reportFile);
}

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
    Client* newClient = new Client(name,dist);
    this->Clients.push_back(newClient);
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

void Base::AddNewBus() {
    Car* bus = new Car(this, "Bus");
    this->Bus.push_back(bus);
}

void Base::AddNewTruck(){
    Car* bus = new Car(this, "TIR");
    this->Truck.push_back(bus);
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

void Package::DeliverPackage(fstream* processFile) {
    for (int i = 0; i < 2; ++i) {
        this->Location->getCenter()->SetBudget(this->Location->getBus()[0]->NeedToTankUp(this->getReceiver()->getDistance(),processFile));
    }
    this->Location->ClearPackages();
    cout << "Paczka numer " << this->getNumOfPackage() << " zostala dostarczona do firmy " << this->receiver->getClientName() << endl;
    *processFile << "Paczka numer " << this->getNumOfPackage() << " zostala dostarczona do firmy " << this->receiver->getClientName() << endl;
    this->getLocation()->getCenter()->AddPackagesDelivered();

}

void Car::placePackageInTruck(Package* package) {
    this->LoadingSpace.push_back(package);
    package->getLocation()->PopPackage();
    this->loadATM+=package->getWeight();
    this->storageATM+=package->getSize();
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

void TakeCareOfPackage(MainBase* Center, int repeatsDone,fstream* processFile){
    Package* newPackage;
    newPackage = Center->CreateNewPackage(repeatsDone,processFile);
    newPackage->CollectPackage(Center,processFile);
    newPackage->checkPackageDestination(Center,processFile);
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        if(Center->getSubBases()[i]->getTruck()[0]->getLoadATM() > 21000 || Center->getSubBases()[i]->getTruck()[0]->getStorageATM()>63){
            Center->getSubBases()[i]->SendTruckToCenter(processFile);
        }
    }
}

double Car::NeedToTankUp(int dist, fstream* processFile) {
    double tempFuel = this->fuelLeft;
    tempFuel -= dist*this->fuelEconomy;
    if(tempFuel<=0){
        this->fuelLeft = (this->fuelTankCapacity + tempFuel);
        cout << "Zatankowano " << this->getType() << " nalezacy do bazy " << this->getOwner()->getCity() << " za kwote " << this->fuelTankCapacity * 5 << " zl" << endl;
        *processFile << "Zatankowano " << this->getType() << " nalezacy do bazy " << this->getOwner()->getCity() << " za kwote " << this->fuelTankCapacity * 5 << " zl" << endl;
        return -(this->fuelTankCapacity * 5);
    }
    else {
        this->fuelLeft = tempFuel;
        return 0;
    }
}

bool checkClients(MainBase* Center){
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        if(Center->getSubBases()[i]->getClients().size() == 0){
            return false;
        }
    }
    return true;
}