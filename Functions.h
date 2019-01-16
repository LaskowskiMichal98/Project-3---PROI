//
// Created by Michał Laskowski on 16/01/2019.
//

#ifndef DELIVERY_COMPANY_FUNCTIONS_H
#define DELIVERY_COMPANY_FUNCTIONS_H

#include "Cars.h"
#include "Packages.h"
#include "Base.h"

MainBase* CreateChain();
int menu(MainBase*,fstream*,fstream*);
void AddNewBaseManually(MainBase*,fstream*,fstream*);
void AddNewClientManually(MainBase*,fstream*,fstream*);
void Simulate(MainBase*,fstream*,fstream*);
bool checkClients(MainBase*);
int randomNumber(int, int);
void TakeCareOfPackage(MainBase*,int,fstream*);

#endif //DELIVERY_COMPANY_FUNCTIONS_H
