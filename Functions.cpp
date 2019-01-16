//
// Created by Michał Laskowski on 16/01/2019.
//

#include "Functions.h"
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
    cin.sync();
    getline(cin,temp);
    if(temp[0]!='0' && temp[0]!='1'&& temp[0]!='2' && temp[0]!='3'){
        throw error;
    }

    switch(temp[0]){
        case '1' : AddNewBaseManually(Center,processFile,reportFile); break;
        case '2' : AddNewClientManually(Center,processFile,reportFile); break;
        case '3' : Simulate(Center,processFile,reportFile); break;
        case '0' : return 0;
    }
    return 0;
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

void AddNewClientManually(MainBase* Center,fstream* processFile,fstream* reportFile){
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
    cin.sync();
    cin >> num;
    cin.sync();
    getline(cin,temp);
    system(CLEAR);
    cout << "Podaj nazwe firmy: ";
    string name;
    cin.sync();
    getline(cin,name);
    cout << "Podaj odleglosc od bazy: ";
    int distance;
    cin.sync();
    cin >> distance;

    Center->getSubBases()[num]->AddClient(name,distance);
    cout << endl << "Utworzono nowego klienta.";


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

int randomNumber(int from, int length){
    return rand() % length + from;
}


bool checkClients(MainBase* Center){
    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        if(Center->getSubBases()[i]->getClients().size() == 0){
            return false;
        }
    }
    return true;
}

void AddNewBaseManually(MainBase* Center,fstream* processFile,fstream* reportFile){
    string city;
    int distance;
    system(CLEAR);
    cout << "Podaj miasto, w ktorym ma zostac utworzona baza: " ;
    cin.sync();
    getline(cin,city);
    cout  << "Podaj odleglosc do bazy glownej (w Lodzi) : " ;
    cin.sync();
    cin >> distance;

    Center->AddNewBase(city,distance);
    Center->getSubBases()[Center->getSubBases().size()-1]->AddNewBus();
    Center->getSubBases()[Center->getSubBases().size()-1]->AddNewTruck();
    cout << "Utworzono nowa baze w " << city << endl;

    string temp;
    cout << "Wcisnij enter aby kontynuowac";
    getline(cin,temp);
    getline(cin,temp);

    menu(Center,processFile,reportFile);
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