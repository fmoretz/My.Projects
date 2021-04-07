#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void PromptLogInMenu(){
  cout << "\n" << "==================" << "CA$H FLOW MANAGER" << "==================" << endl;
  cout << "how can I help you?" << endl;
  cout << "1. log in into existing account" << endl;
  cout << "2. create a new account" << endl;
  cout << "select you choice --> ";
}

void PromptUserMenu(){
  cout << "----------------------------------" << endl;
  cout << "1. deposit" << endl;
  cout << "2. withdraw" << endl;
  cout << "3. check balance" << endl;
  cout << "4. exit account"<< endl;
  cout << "select you choice --> ";
}

string directory = "bin/";
string extension = ".dat";

int main(){

bool log;

while (log == 0){
  char LogIN;
  PromptLogInMenu();
  cin >> LogIN;

  switch(LogIN){
    case '1':{
      string username;
      cout << "Username: ";
      cin >> username;

      string useraccount = directory + username + extension;

      ifstream existing_account(useraccount);
      if(existing_account){cout << "\nlogged successfully!" << "\n" << "welcome back " << username << endl;}
      else {cerr << "no account with name " << username << " exist, please create one" << endl;}

      bool act;

      float balance;
      while(existing_account >> balance)
      {
        cout << "BALANCE:" << balance << endl;
      }

      while(act){
        PromptUserMenu();
        char Menu;
        cin >> Menu;

        switch (Menu) {
          case '1':{
            while(existing_account >> balance)
            {
              cout << "BALANCE:" << balance << endl;
            };
            cout << "How much you want to deposit?";
            float deposit_amount;
            cout << "--> ";
            cin >> deposit_amount;
            balance = deposit_amount+balance;
            cout << "BALANCE: " << balance << "\n" << endl;
            existing_account >> balance;
            break;}

          case '2':{
            while(existing_account >> balance)
            {
              cout << "BALANCE:" << balance << endl;
            }
            cout << "How much you want to withdraw?";
            float withdraw_amount;
            cout << "--> ";
            cin >> withdraw_amount;

            if(withdraw_amount > balance)
            {
              cout << "you cannot withdraw this amount, do you want to make a debt?" <<endl;
              cout << "-[y/n]-> ";
              string debt;
              cin >> debt;
              if(debt == "y")
              {
                balance = balance-withdraw_amount;
                cout << "BALANCE: " << balance << endl;
              }
              else if(debt == "n")
              {
                cout << "withdraw stopped" << endl;
                balance = balance-0;
                cout << "BALANCE: " << balance << endl;
              }
            }
            else
            {
              balance = balance-withdraw_amount;
              cout << "BALANCE: " << balance << endl;
            }
            existing_account >> balance;
            break;}

            case '3':{
              cout << "your balance is: " << balance << endl;
            break;}

            case '4':{
              ofstream existing_account(useraccount);
              existing_account << balance << endl;
              existing_account.close();
              cout << "Good Bye!, please exit the application" << endl;
              act = 1;
              log = 1;
              break;}
        }
      }

    break;}

    case '2':{
      string new_user;
      cout << "Insert your account username: ";
      cin >> new_user;
      string new_account = directory + new_user + extension;

      ofstream new_account_file(new_account);
      new_account_file << 0 <<endl;
      new_account_file.close();
      cout << "account created successfully!" << endl;
      break;}
    }
  }

  cin.get();
  return 0;
}
