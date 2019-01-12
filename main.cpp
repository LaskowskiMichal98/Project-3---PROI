#include <iostream>
#include "Base.h"
using namespace std;

int main() {
    srand(time(nullptr));
    int repeats;
    cout << "Podaj liczbe paczek w symulacji : ";
    cin >> repeats;
    int repeatsDone = 0;

    MainBase *Center = CreateChain();


    while (repeatsDone != repeats) {
        repeatsDone++;
        TakeCareOfPackage(Center, repeatsDone);
    }

    for (int i = 0; i < Center->getSubBases().size(); ++i) {
        if(!Center->getSubBases()[i]->getTruck()[0]->getLoadingSpace().empty()){
            Center->getSubBases()[i]->SendTruckToCenter();
        }
    }

    while(Center->getPackages().size()){
        Center->getPackages()[0]->getDirection()->SendTruckToCenter();
    }
    cout << "Paczki odebrane: " << Center->getPackagesCollected() << endl;
    cout << "Paczki dostarczone: " << Center->getPackagesDelivered() << endl;
}
