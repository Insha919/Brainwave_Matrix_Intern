#include <iostream>
#include <vector>
#include <limits>

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    BankAccount(std::string number, std::string name) : accountNumber(number), accountHolder(name), balance(0.0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: $" << amount << "\n";
        } else {
            std::cout << "Invalid deposit amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawn: $" << amount << "\n";
        } else if (amount > balance) {
            std::cout << "Insufficient funds!\n";
        } else {
            std::cout << "Invalid withdraw amount!\n";
        }
    }

    void transfer(BankAccount& toAccount, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            toAccount.deposit(amount);
            std::cout << "Transferred: $" << amount << " to " << toAccount.getAccountHolder() << "\n";
        } else if (amount > balance) {
            std::cout << "Insufficient funds for transfer!\n";
        } else {
            std::cout << "Invalid transfer amount!\n";
        }
    }

    void checkBalance() const {
        std::cout << "Current balance: $" << balance << "\n";
    }

    std::string getAccountHolder() const {
        return accountHolder;
    }

    std::string getAccountNumber() const {
        return accountNumber;
    }
};

class Bank {
private:
    std::vector<BankAccount> accounts;

public:
    void createAccount() {
        std::string name, number;
        std::cout << "Enter account holder's name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter account number: ";
        std::getline(std::cin, number);
        accounts.emplace_back(number, name);
        std::cout << "Account created for " << name << " with account number " << number << ".\n";
    }

    BankAccount* findAccount(const std::string& number) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == number) {
                return &account;
            }
        }
        return nullptr;
    }

    void menu() {
        int choice;
        do {
            std::cout << "\nBanking System Menu:\n";
            std::cout << "1. Create Account\n";
            std::cout << "2. Deposit\n";
            std::cout << "3. Withdraw\n";
            std::cout << "4. Transfer Money\n";
            std::cout << "5. Check Balance\n";
            std::cout << "6. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            std::string accountNumber;
            double amount;

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    std::cout << "Enter account number: ";
                    std::cin >> accountNumber;
                    if (BankAccount* acc = findAccount(accountNumber)) {
                        std::cout << "Enter amount to deposit: ";
                        std::cin >> amount;
                        acc->deposit(amount);
                    } else {
                        std::cout << "Account not found!\n";
                    }
                    break;
                case 3:
                    std::cout << "Enter account number: ";
                    std::cin >> accountNumber;
                    if (BankAccount* acc = findAccount(accountNumber)) {
                        std::cout << "Enter amount to withdraw: ";
                        std::cin >> amount;
                        acc->withdraw(amount);
                    } else {
                        std::cout << "Account not found!\n";
                    }
                    break;
                case 4:
                    std::cout << "Enter your account number: ";
                    std::cin >> accountNumber;
                    if (BankAccount* fromAcc = findAccount(accountNumber)) {
                        std::string toAccountNumber;
                        std::cout << "Enter the account number to transfer to: ";
                        std::cin >> toAccountNumber;
                        if (BankAccount* toAcc = findAccount(toAccountNumber)) {
                            std::cout << "Enter amount to transfer: ";
                            std::cin >> amount;
                            fromAcc->transfer(*toAcc, amount);
                        } else {
                            std::cout << "Recipient account not found!\n";
                        }
                    } else {
                        std::cout << "Your account not found!\n";
                    }
                    break;
                case 5:
                    std::cout << "Enter account number: ";
                    std::cin >> accountNumber;
                    if (BankAccount* acc = findAccount(accountNumber)) {
                        acc->checkBalance();
                    } else {
                        std::cout << "Account not found!\n";
                    }
                    break;
                case 6:
                    std::cout << "Exiting...\n";
                    break;
                default:
                    std::cout << "Invalid choice! Please select between 1 and 6.\n";
                    break;
            }
        } while (choice != 6);
    }
};

int main() {
    Bank bank;
    bank.menu();
    return 0;
}
