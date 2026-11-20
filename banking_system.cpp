#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const int USER_COUNT = 3;

// Displays the banking menu.
void displayMenu() {
    cout << "\n========== GCC BANK ========="<<endl;
    cout << "1. Deposit"<<endl;
    cout << "2. Withdraw"<<endl;
    cout << "3. Send Cash"<<endl;
    cout << "4. Check Balance"<<endl;
    cout << "5. Exit"<<endl;
    cout << "Enter choice: "<<endl;
}

// Finds a user's position in the arrays using their account number.
int findAccount(const int accountNumbers[], int accountNumber) {
    for (int i = 0; i < USER_COUNT; i++) {
        if (accountNumbers[i] == accountNumber) {
            return i;
        }
    }
    return -1;
}

// Adds a positive amount to the selected user's balance.
void deposit(double balances[], int userIndex) {
    double amount;
    cout << "Enter amount to deposit: R"<<endl;
    if (!(cin >> amount)) {
        cout << "Invalid input. Please enter a number."<<endl;
        cin.clear();

        return;
    }
    if (amount <= 0) {
        cout << "Deposit amount must be more than zero"<<endl;
    } else {
        balances[userIndex] += amount;
        cout << fixed << setprecision(2)<<endl;
        cout << "Deposit successful. New balance: R" << balances[userIndex] << endl;
    }
}

// Withdraws money only when the amount is valid and affordable.
void withdraw(double balances[], int userIndex) {
    double amount;
    cout << "Enter amount to withdraw: R";
    if (!(cin >> amount)) {
        cout << "Invalid input. Please enter a number"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        return;
    }
    if (amount <= 0) {
        cout << "Withdrawal amount must be more than zero"<<endl;
    } else if (amount > balances[userIndex]) {
        cout << "Insufficient funds. Withdrawal cancelled."<<endl;
    } else {
        balances[userIndex] -= amount;
        cout << fixed << setprecision(2);
        cout << "Withdrawal successful. New balance: R" << balances[userIndex] <<endl;
    }
}

// Transfers money to another account if it exists and funds are sufficient.
void sendCash(double balances[], const int accountNumbers[], int senderIndex) {
    int recipientAccount;
    double amount;
    cout << "Enter recipient account number: "<<endl;
    if (!(cin >> recipientAccount)) {
        cout << "Invalid account number"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        return;
    }

    int recipientIndex = findAccount(accountNumbers, recipientAccount);
    if (recipientIndex == -1) {
        cout << "Account not found. Transfer cancelled"<<endl;
        return;
    }
    if (recipientIndex == senderIndex) {
        cout << "You cannot send cash to your own account"<<endl;
        return;
    }

    cout << "Enter amount to send: R";
    if (!(cin >> amount)) {
        cout << "Invalid amount. Please enter a number."<<endl;
        cin.clear();

        return;
    }
    if (amount <= 0) {
        cout << "Transfer amount must be more than zero"<<endl;
    } else if (amount > balances[senderIndex]) {
        cout << "Insufficient funds. Transfer cancelled."<<endl;
    } else {
        balances[senderIndex] -= amount;
        balances[recipientIndex] += amount;
        cout << fixed << setprecision(2);
        cout << "Cash sent successfully to account " << recipientAccount << endl;
        cout << "Your new balance is R" << balances[senderIndex] <<endl;
    }
}

// Displays the balance for the selected user.
void checkBalance(const double balances[], int userIndex) {
    cout << fixed << setprecision(2);
    cout << "Current balance: R" << balances[userIndex] << endl;
}

int main() {
    // The three sample users are stored in parallel arrays.
    string names[USER_COUNT] = {"Dineo Mokoena", "Thabo Nkosi", "Lerato Dlamini"};
    int accountNumbers[USER_COUNT] = {1001, 1002, 1003};
    int pins[USER_COUNT] = {1234, 2345, 3456};
    double balances[USER_COUNT] = {1500.00, 2200.00, 900.00};

    int enteredAccount, enteredPin;
    cout << "========== GCC BANK LOGIN =========="<<endl;
    cout << "Sample accounts for testing: 1001, 1002, 1003"<<endl;
    cout << "Enter account number: ";
    if (!(cin >> enteredAccount)) {
        cout << "Invalid account number. Program closed."<<endl;
        return 0;
    }
    cout << "Enter PIN: "<<endl;
    if (!(cin >> enteredPin)) {
        cout << "Invalid PIN. Program closed"<<endl;
        return 0;
    }

    int currentUser = findAccount(accountNumbers, enteredAccount);
    if (currentUser == -1 || pins[currentUser] != enteredPin) {
        cout << "Incorrect account number or PIN. Access denied"<<endl;
        return 0;
    }

    cout << "Welcome, " << names[currentUser] <<endl;
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a menu number from 1 to 5"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
            continue;
        }

        switch (choice) {
            case 1:
                deposit(balances, currentUser);
                break;
            case 2:
                withdraw(balances, currentUser);
                break;
            case 3:
                sendCash(balances, accountNumbers, currentUser);
                break;
            case 4:
                checkBalance(balances, currentUser);
                break;
            case 5:
                cout << "Thank you for using GCC BANK. Goodbye"<<endl;
                running = false;
                break;
            default:
                cout << "Invalid menu choice. Please choose 1, 2, 3, 4 or 5"<<endl;
        }
    }
    return 0;
}
