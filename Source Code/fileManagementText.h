#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "fileManagementBinary.h"
#include "procedures.h"

int getBalance(){
    int balance;
    string line;
    fstream myBalance;
    myBalance.open("./financial_data/accountBalance.txt",ios::in);
    if(myBalance.is_open()){
        getline(myBalance, line);
        balance = stoi(line);
        myBalance.close();
        return balance;
    }
}

void updateAccountBalance(int amount){
    int balance;
    fstream myBalance;
    string line;
    myBalance.open("./financial_data/accountBalance.txt",ios::in);
    if(myBalance.is_open()){
        getline(myBalance, line);
        balance = stoi(line);
        balance += amount;
        myBalance.close();

    }
    myBalance.open("./financial_data/accountBalance.txt",ios::out);
    if(myBalance.is_open()){
        myBalance << balance;
        myBalance.close();
    }
}

bool is_file_exist(const char *fileName){    //C++ does not have a 'string' data type. To have string, you use char* (pointer points to first char, baki char in string are in adjacent memory positions so it iterates until \0).
    std::ifstream infile(fileName);
    return infile.good();
}