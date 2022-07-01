//
// Created by bethiane on 29/06/22.
//

#include <fstream>
#include <iomanip>
#include "iostream"

using namespace std;

class account{
    int accountNo;
    char name[100];
    char type;
    float amount;

public:
    void createAccount();
    void accountDetails();
    int showAccountNo() const;
    float showBalance() const;
    char showAccountType() const;
    void deposit(float);
    void withdraw(float);
    void report() const;
    void modify();


};

void account::withdraw(float amount) {
    amount-=amount;
}
void account::deposit(float amount) {
    amount+=amount;
}
char account::showAccountType() const{
    return type;
}
int account::showAccountNo() const{
    return accountNo;
}
float account::showBalance() const {
    return amount;
}

void account::report() const {
    cout<<accountNo<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<amount<<endl;
}

void account::createAccount() {
    cout<<"Enter the account number\n";
    cin>>accountNo;
    cout<<"Enter the holder's name\n";
    cin.ignore();
    cin.getline(name,100);
    cout<<"Choose the account type[C/S]\n";
    cin>>type;
    type = toupper(type);
    cout<<"Enter the initial deposit amount\n";
    cin>>amount;
    cout<<"\n ACCOUNT IS CREATED SUCCESSFUL\n";
}

void account::accountDetails(){
    cout<<"\n Account No. : "<<accountNo;
    cout<<"\n Account owner name. : "<<name;
    cout<<"\n Account type. : "<<type;
    cout<<"\n Account balance amount. : "<<amount;
}

void account::modify() {
    cout<<"\n Enter the account number";
    cin>>accountNo;
    cout<<"\n Enter new account holder name:";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\n Enter the new type of account";
    cin>>type;
    type = toupper(type);
    cout<<"\n Enter the new balance";
    cin>>amount;
}


void save_account(){
    account account{};
    ofstream outFile;
    outFile.open("account.dat",fstream::binary| fstream::out | fstream::app);
    account.createAccount();
    outFile.write(reinterpret_cast<char *>(&account), sizeof(account));
    outFile.close();
}

void displayAccountDetails(int accNo){
    account account{};
    bool flag = false;
    ifstream inFile("account.dat");

    if(!inFile){
        cout<<"File can't be opened !! Press any key...";
        return;
    }
    cout<<"\n ACCOUNT DETAILS";
    while(inFile.read(reinterpret_cast<char *>(&account),sizeof (account))){
        if(account.showAccountNo()==accNo){
            account.accountDetails();
            flag = true;
        }
    }
    inFile.close();
    if(!flag){
        cout<<"\n\n Account number does not exist";
    }
}

void display_holders(){
    account account{};
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"The file can't be opened maybe an error occurred.Press an key";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME           Type  Balance\n";
    cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&account), sizeof(account)))
    {
     account.report();
    }
    inFile.close();

}

void modify_account( int accNo){
    bool found = false;
    account account{};
    fstream inFile;
    inFile.open("account.dat", ios::binary|ios::in|ios::out);
    if(!inFile){
        cout<<"You can't open the file";
        return;
    }
    while(!inFile.eof() && !found){
        inFile.read(reinterpret_cast<char *>(&account), sizeof(account));
        if(account.showAccountNo() == accNo){
            account.accountDetails();
            cout<<"Update the account details\n";
            account.modify();
            int pos = (-1)*static_cast<int>(sizeof (account));
            inFile.seekg(pos,ios::cur);
            inFile.write(reinterpret_cast<char *>(&account), sizeof(account));
            cout<<"\n Record is updated";
            found = true;

        }
    }
    inFile.close();
    if(!found)
        cout<<"\n\n Record Not Found";

}

void delete_account(int accNo){
    account account;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"Can't open the file";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&account),sizeof (account))){
        if(account.showAccountNo()!=accNo){
            outFile.write(reinterpret_cast<char *>(&account), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n Record deleted...";
}



    void deposit_money(int accNo){
        float amount;
        bool found = false;
        account account{};
        ifstream inFile;
        inFile.open("account.dat",ios::binary|ios::in|ios::out);
        if(!inFile){
            cout<<"File cannot be found";
            return;
        }
    while(!inFile.eof() && !found){
        inFile.read(reinterpret_cast<char *>(&account), sizeof(account));
        if(account.showAccountNo() == accNo){
            account.accountDetails();
            cout<<"\n TO DEPOSIT AMOUNT";
            cout<<"\n Enter the amount to be deposited";
            cin>>amount;
            account.withdraw(amount);
        }
    }

    }

void withdraw_money(int accNo){
    float amount;
    bool found = false;
    account account{};
    ifstream inFile;
    inFile.open("account.dat",ios::binary|ios::in|ios::out);
    if(!inFile){
        cout<<"File cannot be found";
        return;
    }
    while(!inFile.eof() && !found){
        inFile.read(reinterpret_cast<char *>(&account), sizeof(account));
        if(account.showAccountNo()==accNo){
            account.accountDetails();
            cout<<"\n TO DEPOSIT AMOUNT";
            cout<<"\n Enter the amount to be deposited";
            cin>>amount;
            float balance = account.showBalance() -amount;
            if((balance<500 && account.showAccountType() == 'S')|| (balance<1000 && account.showAccountType() == 'C')){
                cout<<"Insufficient balance";
            }
            else{
                account.withdraw(amount);
            }
            account.withdraw(amount);
        }

//    int pos=(-1)*static_cast<int>(sizeof(account));
//    inFile.seekp(pos,ios::cur);
//    inFile.write(reinterpret_cast<char *> (&account), sizeof(account));
//    cout<<"\n\n\t Record Updated";
//    found=true;
}
    inFile.close();
    cout << "\n Record not found";
}

void intro(){
    cout<<"\t\t\t==================================================\n";
    cout<<"\t\t\t==================================================\n";
    cout<<"\t\t\t==========\t      WARM WELCOME TO     \t==========\n";
    cout<<"\t\t\t==========\t         Gen-Z Bank       \t==========\n";
    cout<<"\t\t\t==================================================\n";
    cout<<"\t\t\t==================================================\n";
    cout<<"\t\t\t\nPress any key to continue\n";
    cin.get();
}


int main(){
    intro();
    char choice;
    int accountNumber;
    do{
        cout<<"\t\t\t==================================================\n";
        cout<<"\t\t\t                        MENU                      \n";
        cout<<"\t\t\t==================================================\n";
        cout<<"\t\t\t======\t          1.CREATE ACCOUNT        \t======\n";
        cout<<"\t\t\t======\t          2.DEPOSIT AMOUNT        \t======\n";
        cout<<"\t\t\t======\t          3.WITHDRAW AMOUNT       \t======\n";
        cout<<"\t\t\t======\t          4.BALANCE ENQUIRY       \t======\n";
        cout<<"\t\t\t======\t          5.ACCOUNT HOLDERS       \t======\n";
        cout<<"\t\t\t======\t          6.CLOSE ACCOUNT         \t======\n";
        cout<<"\t\t\t======\t          7.MODIFY AN ACCOUNT     \t======\n";
        cout<<"\t\t\t======\t          8.EXIT                  \t======\n";
        cout<<"\t\t\t==================================================\n";
        cout<<"\t\t\t==================================================\n";
        cout<<"Enter your choice\n";
        cin>>choice;
        switch (choice) {
            case '1':
                save_account();
                break;
            case '2':
                cout<<"Enter the account number";
                cin>>accountNumber;
                deposit_money(accountNumber);
                break;
            case '3':
                cout<<"Enter the account number";
                cin>>accountNumber;
                withdraw_money(accountNumber);
                break;
            case '4':
                cout<<"Enter the account number";
                cin>>accountNumber;
                displayAccountDetails(accountNumber);
                break;
            case '5':
                display_holders();
                break;
            case '6':
                cout<<"Enter the account number";
                cin>>accountNumber;
                delete_account(accountNumber);
                break;
            case '7':
                cout<<"Enter the account number";
                cin>>accountNumber;
                modify_account(accountNumber);
                break;
            case '8':
                break;
            default:
                cout<<"Invalid option!"<<endl;
                break;
        }

    } while (choice!='8');

    return 0;

    }



