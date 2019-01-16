#include <iostream>
#include <fstream>
#include "Base.h"
using namespace std;

int main() {

    fstream processFile;
    fstream reportFile;
    processFile.open("process.txt",ios::out);
    reportFile.open("report.txt",ios::out);
    srand(time(nullptr));
    MainBase *Center = CreateChain();

    while(1) {
        try {
            if(!menu(Center,&processFile,&reportFile)){
                break;
            }
        }
        catch (string s) {
            cout << s;
            string temp;
            cout << endl << "Wcisnij enter aby kontynuowac";
            getline(cin, temp);
        }
    }
}
