#include <iostream>   // library for cin, cout
#include <fstream>    // library for file handling
#include <string>     // library for strings
#include <windows.h>  // library for console color
using namespace std;

// Structure to hold account details
struct Account {
    int balance;
    int pin;
};

// Declaration of functions or function prototype
double withdrawal(Account& account);
double deposit(Account& account);
double fundtransfer(Account& account);
double changePIN(Account& account);
void saveData(const Account& account);
void loadData(Account& account);

// Function to set console text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Initializing several variables
int main() {
    Account account; // Using structure to store account details
    char option;
    int input_pin; // Variable to store user-entered PIN

    loadData(account); // Load balance and PIN from a file using the 'loadData' function

    do {
        // Loop will continue to run if the password is correct until the user chooses to exit (option 'F')
        while (true) {
            setColor(11); // Cyan text
            cout << "--------Welcome to Habib Bank Limited-------" << endl;
            cout << "\nPlease Insert your Card" << endl;
            cout << "\nENTER YOUR PIN" << endl;
            cin >> input_pin;

            // If the password is correct
            if (input_pin == account.pin) {
                setColor(10); // Green text
                cout << "\t\t\t\t\t*Your transaction has been processed*\t\t\t\t\t" << endl;
                cout << endl;
                break;
            }
            // If the password is not valid
            else {
                setColor(12); // Red text
                cout << "INVALID PIN. Please Try Again" << endl;
            }
        }

        // User will select the mode of transaction
        setColor(14); // Yellow text
        cout << "Please Select Your Mode Of Transaction" << endl;
        cout << "\nA. Withdrawal" << endl;
        cout << "B. Deposit" << endl;
        cout << "C. Fund Transfer" << endl;
        cout << "D. Balance Inquiry" << endl;
        cout << "E. Change PIN" << endl;
        cout << "F. EXIT" << endl;
        cout << endl;
        cin >> option;

        // Execute the corresponding function based on user input
        switch (option) {
        case 'A':
            withdrawal(account); // Call withdrawal function
            break;
        case 'B':
            deposit(account);  // Call deposit function
            break;
        case 'C':
            fundtransfer(account);  // Call fundtransfer function
            break;
        case 'D':
            setColor(10); // Green text
            cout << "Your Current Balance is " << account.balance << endl; // Display current balance
            break;
        case 'E':
            changePIN(account); // Call changePIN function
            break;
        case 'F':
            setColor(11); // Cyan text
            cout << "Thank you for using this ATM" << endl;
            break;
        default:
            setColor(12); // Red text
            cout << "Invalid Option. Please try again." << endl;
        }
        cout << endl;
        setColor(13); // Magenta text
        cout << "\t\t\t\t\t\tTHANK YOU!\t\t\t\t\t\t\t\t\t" << endl;
        cout << "\t\t\t\t\t*Please take your card*\t\t\t\t\t" << endl;
        cout << endl;

        // Save balance and PIN to file after each transaction using the saveData function
        saveData(account);

    } while (option != 'F');  // Loop will end if the user enters F

    return 0;
}

double withdrawal(Account& account) {
    int amount;    // Variable to store the amount for the transaction
    cout << "Please enter the amount for the transaction" << endl;
    cin >> amount;
    cout << endl;

    // If condition is valid
    if (amount > 0 && amount <= account.balance) {
        setColor(10); // Green text
        cout << "TRANSACTION SUCCESSFUL" << endl;
        cout << "Please Collect Your Cash" << endl;
        account.balance -= amount;  // Deduct the amount from the balance
        cout << "Your Remaining Balance is " << account.balance << endl;
    }
    // If condition is not valid
    else {
        setColor(12); // Red text
        cout << "INSUFFICIENT FUNDS" << endl;
    }
    return account.balance; // Return the updated balance
}

double deposit(Account& account) {
    int amount;   // Variable to store the amount for the transaction
    cout << "Enter the amount you want to deposit" << endl;
    cin >> amount;
    cout << endl;

    // If condition is valid
    if (amount > 0) {
        setColor(10); // Green text
        cout << "DEPOSIT SUCCESSFUL" << endl;
        account.balance += amount;  // Add the amount to the balance
        cout << "Your new balance is " << account.balance << endl;
    }
    // If condition is not valid
    else {
        setColor(12); // Red text
        cout << "INVALID DEPOSIT. Please Try Again" << endl;
    }
    return account.balance;  // Return the updated balance
}

double fundtransfer(Account& account) {
    int amount;    // Variable to store the amount for the transaction
    cout << "Enter the amount you want to transfer" << endl;
    cin >> amount;
    cout << endl;

    // If condition is valid
    if (amount > 0 && amount <= account.balance) {
        setColor(10); // Green text
        cout << "Your amount has been transferred" << endl;
        account.balance -= amount; // Deduct the amount from the balance
        cout << "Your remaining balance is " << account.balance << endl;
    }
    // If condition is not valid
    else {
        setColor(12); // Red text
        cout << "INVALID TRANSFER" << endl;
    }
    return account.balance;   // Return the updated balance
}

double changePIN(Account& account) {
    int old_pin, new_pin, confirm_pin;
    cout << "Enter Your Previous PIN" << endl;
    cin >> old_pin;

    // Check if the old PIN entered matches the current PIN
    if (old_pin == account.pin) {
        cout << "Enter your new PIN" << endl;
        cin >> new_pin;
        cout << "Confirm your new PIN" << endl;
        cin >> confirm_pin;

        // Check if the new PIN and confirmed new PIN match
        if (new_pin == confirm_pin) {
            account.pin = new_pin;  // Update the PIN to the new PIN
            setColor(10); // Green text
            cout << "Your PIN has been changed successfully to " << new_pin << endl;
        }
        else {
            setColor(12); // Red text
            cout << "New PIN and confirm PIN do not match. Please try again." << endl;
        }
    }
    else {
        // Inform the user that the old PIN entered is incorrect
        setColor(12); // Red text
        cout << "OLD PIN INCORRECT" << endl;
    }
    return account.pin;  // Return the updated PIN
}

// Function to save balance and PIN to file
void saveData(const Account& account) {
    ofstream outfile("account_data.txt");
    if (outfile.is_open()) {
        outfile << account.balance << endl;  // Write balance to the file
        outfile << account.pin << endl;      // Write PIN to the file
        outfile.close();
    }
    else {
        setColor(12); // Red text
        cout << "Unable to open file for writing." << endl;
    }
}

// Function to load balance and PIN from file
void loadData(Account& account) {
    ifstream infile("account_data.txt");
    if (infile.is_open()) {
        infile >> account.balance;  // Read balance from the file
        infile >> account.pin;      // Read PIN from the file
        infile.close();
    }
    else {
        // Set default values if file does not exist
        account.balance = 50000;
        account.pin = 1926;
    }
}