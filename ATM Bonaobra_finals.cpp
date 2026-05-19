#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

class Account {
public:
    string id;
    string name;
    string pin;
    double balance;

    void displayBalance() {
        cout << "\n================================" << endl;
        cout << "  ACCOUNT HOLDER: " << name << endl;
        cout << "  CURRENT BALANCE: Php " << balance << endl;
        cout << "================================" << endl;
    }
};

int main() { 
    Account list[10]; 
    int accountCount = 0;

    // --- IMPROVED FILE LOADING SECTION ---
    ifstream file("account.txt");
    
    // If the file is missing, create it automatically!
    if (!file) {
        ofstream createNew("account.txt");
        createNew << "101 Juan 1234 5000.0" << endl;
        createNew << "102 Maria 0000 2500.0" << endl;
        createNew << "103 Isla 8888 1000.0" << endl;
        createNew << "104 Carlo 3131 1555.0" << endl;
        createNew << "105 Juzian 4141 1888.0" << endl;
        createNew << "106 Louige 5555 1999.0" << endl;
        createNew << "107 Tristan 9999 3333.0" << endl;
        createNew << "108 Emman 2424 1000.0" << endl;
        createNew << "109 Jhonmar 11111 1100.0" << endl;
        createNew << "110 Inee 1313 1000.0" << endl;
        createNew.close();
        
        // Now open the newly created file
        file.open("account.txt");
    }

    while (accountCount < 10 && file >> list[accountCount].id >> list[accountCount].name >> list[accountCount].pin >> list[accountCount].balance) {
        accountCount++;
    }
    file.close();
    // -------------------------------------

    string inputName, inputPin;
    int foundIndex = -1;

    cout << "--- ATM BANKING SYSTEM ---" << endl;
    cout << "Enter Account Name: ";
    cin >> inputName;
    cout << "Enter PIN: ";
    cin >> inputPin;

    for (int i = 0; i < accountCount; i++) {
        if (list[i].name == inputName && list[i].pin == inputPin) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "\n[!] Invalid Name or PIN. Access Denied." << endl;
        return 0; 
    }

    int choice = 0;
    while (choice != 5) {
        cout << "\nWelcome back, " << list[foundIndex].name << "!" << endl;
        cout << "1. Check Balance\n2. Deposit Money\n3. Withdraw Money\n4. Change PIN\n5. Exit" << endl;
        cout << "Select transaction: ";
        cin >> choice;

        if (choice == 1) {
            list[foundIndex].displayBalance();
        } 
        else if (choice == 2) {
            double amount;
            cout << "Enter deposit amount: ";
            cin >> amount;
            if (amount > 0) {
                list[foundIndex].balance += amount;
                cout << "Successfully deposited Php " << amount << endl;
            }
        } 
        else if (choice == 3) {
            double amount;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            if (amount > list[foundIndex].balance) {
                cout << "Insufficient balance!" << endl;
            } else if (amount > 0) {
                list[foundIndex].balance -= amount;
                cout << "Successfully withdrew Php " << amount << endl;
            }
        } 
        else if (choice == 4) {
            string newPin;
            cout << "Enter new 4-digit PIN: ";
            cin >> newPin;
            list[foundIndex].pin = newPin;
            cout << "PIN updated successfully!" << endl;
        }
        else if (choice == 5) {
            cout << "Saving data... Goodbye!" << endl;
            
            // Save all changes back to the file
            ofstream outFile("account.txt");
            for(int i = 0; i < accountCount; i++) {
                outFile << list[i].id << " " << list[i].name << " " << list[i].pin << " " << list[i].balance << endl;
            }
            outFile.close();
        }
    }

    return 0;
}
/*
1 Juan 1234 5000
2 Maria 0000 2500
3 Isla 8888 1000
4 Carlo 3131 1555
5 Juzian 4141 1888
6 Louige 5555 1999
7 Tristan 9999 3333
8  Emman 2424 1000
9 Jhonmar 11111 1100
10 Inee 1313 1000
*/