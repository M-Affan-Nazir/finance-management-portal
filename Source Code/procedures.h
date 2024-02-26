#include <string>
#include <ctime>

string getReason();

void displayHeader(){
    cout << "\t\t -----------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t $ PERSONAL FINANCE MANAGEMENT $" << endl;
    cout << "\t\t -----------------------------------------------------------------------------------" << endl;
    cout << "\n" << endl;
}

void deposit(){
    int amountToSubmit;
    system("cls");
    displayHeader();
    cout << "\t\t\t\t\t   <<   DEPOSIT TO ACCOUNT   >>" << endl;
    cout << "\n" << endl;
    cout << " > AMOUNT TO SUBMIT: $";
    cin >> amountToSubmit;
    if(amountToSubmit < 0){
        amountToSubmit = -amountToSubmit;
    }
    updateAccountBalance(amountToSubmit);
    std::time_t ms = std::time(nullptr);  //ms elapsed since epoch
    string buf("dp-");
    buf.append(to_string(amountToSubmit));
    buf.append("-");
    buf.append(to_string(ms));
    addTransactionHistory(buf);
}

void withdraw(){
    int amountToWithdraw;
    string reason;
    system("cls");
    displayHeader();
    cout << "\t\t\t\t\t <<   WITHDRAW FROM ACCOUNT   >>" << endl;
    cout << "\n" << endl;
    cout << " > AMOUNT TO WITHDRAW: $";
    cin >> amountToWithdraw;
    if(amountToWithdraw < 0){
        amountToWithdraw = -amountToWithdraw;
    }
    updateAccountBalance(-amountToWithdraw);

    reason = getReason();
    std::time_t ms = std::time(nullptr);
    string buf("wd-");
    buf.append(to_string(amountToWithdraw));
    buf.append("-");
    buf.append(to_string(ms));
    buf.append("-");
    buf.append(reason);
    addTransactionHistory(buf);
}

void transferToEmergencyFund(){
    int amountToTransfer;
    system("cls");
    displayHeader();
    cout << "\t\t\t\t    <<   TRANSFER TO EMERGENCY FUND   >>" << endl;
    cout << "\n" << endl;
    cout << " > AMOUNT TO TRANSFER: $";
    cin >> amountToTransfer;
    if(amountToTransfer < 0){
        amountToTransfer = -amountToTransfer;
    }
    updateAccountBalance(-amountToTransfer);
    updateEmergencyFund(amountToTransfer);
    cout << " > $" << amountToTransfer << " TRANSFERED FROM ACCOUNT --> EMERGENCY FUND" << endl;
    system("pause>nul");
}

void withdrawFromEmf(){
    int amountToWithdraw;
    system("cls");
    displayHeader();
    cout << "\t\t\t\t   <<   WITHDRAW FROM EMERGENCY FUND   >>" << endl;
    cout << "\n" << endl;
    cout << " > AMOUNT TO WITHDRAW: $";
    cin >> amountToWithdraw;
    if(amountToWithdraw < 0){
        amountToWithdraw = -amountToWithdraw;
    }
    updateEmergencyFund(-amountToWithdraw);
    std::time_t ms = std::time(nullptr);
    string buf("wd-");
    buf.append(to_string(amountToWithdraw));
    buf.append("-");
    buf.append(to_string(ms));
    buf.append("-em");   //emergency
    addTransactionHistory(buf);
}

void printDetails(){
    system("cls");
    displayHeader();
    cout << "\t\t\t\t\t   <<   ACCOUNT DETAILS   >>" << endl;
    cout << "\n" << endl;
    int balance = getBalance();
    int emfBalance = getEmfBalance();
    cout << " > ACCOUNT BALANCE = $" << balance << endl;
    cout << " > EMERGENCY FUND = $" << emfBalance << endl;
    system("pause>nul");
}

string getReason(){
    bool flag = false;
    int res;
    cout << "\t1. FOOD" <<endl;
    cout << "\t2. BILLS/RENT" <<endl;
    cout << "\t3. TRANSPORTATION" <<endl;
    cout << "\t4. NECESSITY" <<endl;
    cout << "\t5. LEISURE" <<endl;
    while(flag == false){
        cout << " > (REQUIRED) PLEASE SELECT REASON FOR WITHDRAWAL: ";
        cin >> res;
        if(res == 1){
            return "fd";
            flag == true;
        }
        else if (res == 2){
            return "bl";
            flag == true;
        }
        else if (res == 3){
            return "tp";
            flag == true;
        }
        else if (res == 4){
            return "ns";
            flag == true;
        }
        else if (res == 5){
            return "ls";
            flag == true;
        }
    }
}