/*
  rec03.cpp
  Sec C, Feb 14, 2020
  Hongyi Zheng
  Implement the structure representing bank account and demonstrate its usage.
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Account POD
struct Account {
  string name;
  int account_num;
};

// Account ADT
class AccountV2 {
  // grant access to privte variables
  friend ostream &operator<<(ostream &os, const AccountV2 &account);

public:
  // initialization list
  AccountV2(const string &theName, int theAccountNumber)
      : name(theName), account_num(theAccountNumber), balance(0) {}

  // getter
  // string getName() const { return name; }
  // getAccountNumber() can't be remarked since searching account in a vector
  // requires account number
  int getAccountNumber() const { return account_num; }

  // deposit and withdrawal methods
  void deposit(int amount) {
    transaction_history.emplace_back("deposit", amount);
    balance += amount;
  }

  void withdrawal(int amount) {
    // if funds are insufficient, generate an error and exit
    if (balance < amount) {
      cerr << "insufficient funds";
      return;
    }
    transaction_history.emplace_back("withdrawal", amount);
    balance -= amount;
  }

private:
  // embedded Transaction class. Cannot be accessed from outside
  class Transaction {
  public:
    Transaction(const string &theType, int theAmount)
        : type(theType), amount(theAmount) {}

  private:
    string type;
    int amount;
  };

  string name;
  int account_num;
  vector<Transaction> transaction_history;
  int balance;
};

// prototypes
void openFile(ifstream &fileStream, const string &filename);
void displayAccountVector(const vector<Account> &accountVector);
void displayAccountV2Vector(const vector<AccountV2> &accountVector);
ostream &operator<<(ostream &os, const AccountV2 &account);
void depositintoAccount(vector<AccountV2> &accountVector, int account_num,
                        int amount);
void withdrawfromAccount(vector<AccountV2> &accountVector, int account_num,
                         int amount);

int main() {
  ifstream accountStream;
  openFile(accountStream, "accounts.txt");

  string name;
  int account_num;
  vector<Account> account_structs;

  // Directly assisgn values to fields after declaration
  while (accountStream >> name >> account_num) {
    Account new_account;
    new_account.name = name;
    new_account.account_num = account_num;
    account_structs.push_back(new_account);
  }
  accountStream.close();
  displayAccountVector(account_structs);

  account_structs.clear();
  openFile(accountStream, "accounts.txt");
  // Use curly braced initializers to initialze Account
  while (accountStream >> name >> account_num) {
    Account new_account{name, account_num};
    account_structs.push_back(new_account);
  }
  accountStream.close();
  displayAccountVector(account_structs);

  vector<AccountV2> account_classes;
  openFile(accountStream, "accounts.txt");
  while (accountStream >> name >> account_num) {
    // Initilize Account ADT with constructor
    AccountV2 new_account(name, account_num);
    // add copyies of Account into vector
    account_classes.push_back(new_account);
  }
  accountStream.close();
  displayAccountV2Vector(account_classes);

  account_classes.clear();
  openFile(accountStream, "accounts.txt");
  while (accountStream >> name >> account_num) {
    // push back temporary instances
    account_classes.push_back(AccountV2(name, account_num));
  }
  accountStream.close();

  account_classes.clear();
  openFile(accountStream, "accounts.txt");
  while (accountStream >> name >> account_num) {
    // initalize instances in vector
    account_classes.emplace_back(name, account_num);
  }
  accountStream.close();
  displayAccountV2Vector(account_classes);

  account_classes.clear();
  ifstream transactionStream;
  openFile(transactionStream, "transactions.txt");
  string command;
  int amount;
  // read command first, then read next two tokens into different type of
  // variables according to the command
  while (transactionStream >> command) {
    if (command == "Account") {
      transactionStream >> name >> account_num;
      account_classes.emplace_back(name, account_num);
    } else if (command == "Deposit") {
      transactionStream >> account_num >> amount;
      depositintoAccount(account_classes, account_num, amount);
    } else {
      transactionStream >> account_num >> amount;
      withdrawfromAccount(account_classes, account_num, amount);
    }
  }
}

// functions
// try to open a specified file, output an error if failed to open it
void openFile(ifstream &fileStream, const string &filename) {
  fileStream.clear();
  fileStream.open(filename);
  // check if the file is succesfully opened
  if (!fileStream) {
    cerr << "failed to open " << filename;
    exit(1);
  }
}

// display the information of all Account POD in the vector
void displayAccountVector(const vector<Account> &accountVector) {
  for (const Account &curr_account : accountVector) {
    cout << "name: " << curr_account.name
         << " account number: " << curr_account.account_num << endl;
  }
}

// display the information of all Account ADT in the vector
void displayAccountV2Vector(const vector<AccountV2> &accountVector) {
  for (const AccountV2 &curr_account : accountVector) {
    //  cout << "name: " << curr_account.getName()
    //       << " account number: " << curr_account.getAccountNumber() << endl;
    cout << curr_account;
  }
}

// operator overload
ostream &operator<<(ostream &os, const AccountV2 &account) {
  // os << "name: " << account.getName()
  //    << " account number: " << account.getAccountNumber() << endl;
  os << "name: " << account.name << " account number: " << account.account_num
     << endl;
  return os;
}

// search for the account using account number, then call the deposit method of
// Account
void depositintoAccount(vector<AccountV2> &accountVector, int account_num,
                        int amount) {
  for (AccountV2 &curr_account : accountVector) {
    if (curr_account.getAccountNumber() == account_num) {
      curr_account.deposit(amount);
      return;
    }
  }
}

// search for the account using account number, then call the withdrawal method
// of Account
void withdrawfromAccount(vector<AccountV2> &accountVector, int account_num,
                         int amount) {
  for (AccountV2 &curr_account : accountVector) {
    if (curr_account.getAccountNumber() == account_num) {
      curr_account.withdrawal(amount);
      return;
    }
  }
}
