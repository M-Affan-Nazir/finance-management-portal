#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "fileManagementBinary.h"
#include "procedures.h"

void displayMenu(){

    int res;
    
    displayHeader();
    
    cout << "    ---------------------------------------" << endl;
    cout << "   |\t1. PRINT DETAILS                  |" << endl; 
    cout << "   |\t2. DEPOSIT                        |" << endl;
    cout << "   |\t3. WITHDRAW                       |" << endl;
    cout << "   |\t4. TRANSFER TO EMERGENCY FUND     |" << endl;
    cout << "   |\t5. WITHDRAW FRON EMERGENCY FUND   |" << endl;
    cout << "    ---------------------------------------" << endl;
    cout << "\n" << endl;
    cout << " > ENTER OPTION: ";
    cin >> res;
    if(res == 1){
        printDetails();
    }
    else if (res == 2){
        deposit();
    }
    else if (res == 3){
        withdraw();
    }
    else if (res == 4){
        transferToEmergencyFund();
    }
    else if (res == 5){
        withdrawFromEmf();
    }

}

int main(){
    system("mkdir financial_data");
    initialization();
    system("title PERSONAL FINANCE MANAGEMENT");
    system("color 7D");
    system("cls");
    while(true){
        displayMenu();
        system("cls");
    }
    return 0;
}