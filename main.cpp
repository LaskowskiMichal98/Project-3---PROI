#include <iostream>
#include "Base.h"
using namespace std;

int main() {
    srand(time(nullptr));
    int repeats;
    cout << "Podaj liczbe paczek w symulacji : ";
    cin >> repeats;
    int repeatsDone = 0;

    MainBase* Center = CreateChain();

    while(repeatsDone!=repeats){
        repeatsDone++;
        Center->CreateNewPackage(repeatsDone);
    }
}