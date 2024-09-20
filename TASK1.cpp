#include <iostream>
#include <string>

class ATM {
private:
    std::string accountNumber;
    std::string pin;
    double balance;

public:
    ATM(std::string accNum, std::string pinCode, double initialBalance) 
        : accountNumber(accNum), pin(pinCode), balance(initialBalance) {}

    bool validatePin(const std::string& inputPin) {
        return inputPin == pin;
    }

    void displayMenu() {
        std::cout << "\n*** ATM Menu ***\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Exit\n";
        std::cout << "Select an option: ";
    }

    void checkBalance() {
        std::cout << "Current balance: $" << balance << "\n";
    }

    void deposit() {
        double amount;
        std::cout << "Enter amount to deposit: $";
        std::cin >> amount;
        if (amount > 0) {
            balance += amount;
            std::cout << "Successfully deposited $" << amount << ". New balance: $" << balance << "\n";
        } else {
            std::cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw() {
        double amount;
        std::cout << "Enter amount to withdraw: $";
        std::cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Successfully withdrew $" << amount << ". New balance: $" << balance << "\n";
        } else {
            std::cout << "Invalid withdrawal amount or insufficient funds.\n";
        }
    }
};

int main() {
    std::string accountNumber;
    std::string pin;
    
    std::cout << "Enter your account number: ";
    std::cin >> accountNumber;
    std::cout << "Enter your PIN: ";
    std::cin >> pin;

    // Initialize ATM with a dummy account for demonstration
    ATM atm(accountNumber, pin, 1000.00);

    std::string enteredPin;
    std::cout << "Please enter your PIN to access your account: ";
    std::cin >> enteredPin;

    if (!atm.validatePin(enteredPin)) {
        std::cout << "Invalid PIN. Access denied.\n";
        return 1;
    }

    int option;
    do {
        atm.displayMenu();
        std::cin >> option;

        switch (option) {
            case 1:
                atm.checkBalance();
                break;
            case 2:
                atm.deposit();
                break;
            case 3:
                atm.withdraw();
                break;
            case 4:
                std::cout << "Exiting. Thank you!\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (option != 4);

    return 0;
}
