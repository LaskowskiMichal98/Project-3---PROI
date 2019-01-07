#include <iostream>
#include "Cars.h"
using namespace std;

int main() {
    srand(time(nullptr));
//    int repeats;
//    cout << "Podaj liczbe paczek w symulacji :" << endl;
//    cin >> repeats;

    MainBase* Center = CreateChain();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << Center->getSubBases()[i]->getClients()[j]->getClientName() << endl;
        }
    }

}