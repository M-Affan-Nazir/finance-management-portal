#include <fstream>
#include <string>
#include <ctime>

void addBalanceHistory(uint32_t amount){
    string toAdd;
    fstream balance;
    toAdd = to_string(amount);
    std::time_t ms = std::time(nullptr);
    toAdd.append("-");
    toAdd.append(to_string(ms));
    balance.open("./financial_data/bh.fmd",ios::binary | ios::out | ios::app);
    for(char&c : toAdd){
        balance.write((char*)&c,sizeof(c));
    }
    int space = 32;
    balance.write((char*)&space,sizeof(space));
    balance.close();
}

void addEfHistory(uint32_t amount){
    string toAdd;
    fstream balance;
    toAdd = to_string(amount);
    std::time_t ms = std::time(nullptr);
    toAdd.append("-");
    toAdd.append(to_string(ms));
    balance.open("./financial_data/efh.fmd",ios::binary | ios::out | ios::app);
    for(char&c : toAdd){
        balance.write((char*)&c,sizeof(c));
    }
    int space = 32;
    balance.write((char*)&space,sizeof(space));
    balance.close();
}

void updateAccountBalance(uint32_t amount){
    uint32_t accountBalance;
    fstream balance;
    balance.open("./financial_data/accountBalance.fmd",ios::binary | ios::in);
    balance.read((char*)&accountBalance,sizeof(accountBalance));
    balance.close();
    accountBalance += amount;
    balance.open("./financial_data/accountBalance.fmd",ios::binary | ios::out);
    balance.write((char*)&accountBalance,sizeof(accountBalance));
    balance.close();
    addBalanceHistory(accountBalance);
}

int getBalance(){
    uint32_t accountBalance;
    fstream balance;
    balance.open("./financial_data/accountBalance.fmd",ios::binary | ios::in);
    balance.read((char*)&accountBalance,sizeof(accountBalance));
    balance.close();
    return accountBalance;   
}

int getEmfBalance(){
    uint32_t emf;
    fstream emfbalance;
    emfbalance.open("./financial_data/emf.fmd",ios::binary | ios::in);
    emfbalance.read((char*)&emf,sizeof(emf));
    emfbalance.close();
    return emf;
}

void updateEmergencyFund(uint32_t amount){
    uint32_t emf;
    fstream emfbalance;
    emfbalance.open("./financial_data/emf.fmd",ios::binary | ios::in);
    emfbalance.read((char*)&emf,sizeof(emf));
    emfbalance.close();
    emf += amount;
    emfbalance.open("./financial_data/emf.fmd",ios::binary | ios::out);
    emfbalance.write((char*)&emf,sizeof(emf));
    emfbalance.close();
    addEfHistory(emf);
}

void addTransactionHistory(string data){
    fstream th;
    th.open("./financial_data/th.fmd",ios::binary | ios::out | ios::app);
    for(char&c : data){
        th.write((char*)&c,sizeof(c));
    }
    int space = 32;
    th.write((char*)&space,sizeof(space));
    th.close();
}

bool is_file_exist(const char *fileName){    //C++ does not have a 'string' data type. To have string, you use char* (pointer points to first char, baki char in string are in adjacent memory positions so it iterates until \0).
    std::ifstream infile(fileName);
    return infile.good();
}

void initialization(){
    //runs only when being created first time
    
    if(is_file_exist("./financial_data/accountBalance.fmd") == false){
        uint32_t accountBalance = 0;
        fstream balance;
        balance.open("./financial_data/accountBalance.fmd",ios::binary | ios::out);
        balance.write((char*)&accountBalance,sizeof(accountBalance));
        balance.close();
    }
    if(is_file_exist("./financial_data/emf.fmd") == false){
        uint32_t accountBalance = 0;
        fstream balance;
        balance.open("./financial_data/emf.fmd",ios::binary | ios::out);
        balance.write((char*)&accountBalance,sizeof(accountBalance));
        balance.close();
    }
}

// void readTransactionHistory(){
//     fstream th;
//     int ascii;
//     th.open("./financial_data/th.fmd",ios::binary | ios::in);
//     while(th.read((char*)&ascii, sizeof(ascii))){
//         if(ascii == 32 ){  // rather than printing space, go to next line- ASICC of Space = 32
//             cout << "\n" << endl;
//         }
//         else{
//             cout << char(ascii);
//         }
//     }
//     system("pause>nul");
// }