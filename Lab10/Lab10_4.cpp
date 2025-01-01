#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Bank Account class
class BankAccount {
public:
    BankAccount(int id, double balance) : id(id), balance(balance) {}

    // Copy constructor
    BankAccount(const BankAccount& other) : id(other.id), balance(other.balance) {}

    // Deposit money into the account
    void deposit(double amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balance += amount;
        std::cout << "Deposited " << amount << " to account " << id << ". New balance: " << balance << std::endl;
    }

    // Withdraw money from the account
    void withdraw(double amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrew " << amount << " from account " << id << ". New balance: " << balance << std::endl;
        } else {
            std::cout << "Insufficient funds in account " << id << std::endl;
        }
    }

    // Get the account balance
    double getBalance() const {
        std::lock_guard<std::mutex> lock(mtx);
        return balance;
    }

private:
    int id;
    double balance;
    mutable std::mutex mtx; // Mutex to protect the balance
};

// Function to simulate deposits
void depositMoney(BankAccount &account, double amount, int times) {
    for (int i = 0; i < times; ++i) {
        account.deposit(amount);
    }
}

// Function to simulate withdrawals
void withdrawMoney(BankAccount &account, double amount, int times) {
    for (int i = 0; i < times; ++i) {
        account.withdraw(amount);
    }
}

int main() {
    // Create bank accounts
    std::vector<BankAccount> accounts = {
        BankAccount(1, 1000.0),
        BankAccount(2, 2000.0),
        BankAccount(3, 3000.0)
    };

    // Create threads for deposits and withdrawals
    std::vector<std::thread> threads;

    // Simulate deposits
    for (auto &account : accounts) {
        threads.push_back(std::thread(depositMoney, std::ref(account), 100.0, 5));
    }

    // Simulate withdrawals
    for (auto &account : accounts) {
        threads.push_back(std::thread(withdrawMoney, std::ref(account), 50.0, 5));
    }

    // Join all threads
    for (auto &thread : threads) {
        thread.join();
    }

    // Print final balances
    for (const auto &account : accounts) {
        std::cout << "Final balance of account " << account.getBalance() << std::endl;
    }

    return 0;
}
