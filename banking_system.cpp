#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

// database
string name, password;

// parameters for drawGUI function
enum Sections{
    TRANSACTIONS = 1,
    REGISTRATION

};

void drawUI(int section){
    switch(section){
        case 1:
            cout << "Transactions:\n\n";
            cout << "1 - Login\n";
            cout << "2 - Register\n";
            cout << "3 - Exit\n";
            break;
        case 2:
            cout << "Account Registration:\n\n";
            break;
    }
}

void errorHandler(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void registerAccount(string name, string password, float balance){
    ofstream file("data.csv", ios::app);

    // error handling
    if(!file.is_open()) cerr << "Failed to open file: data.csv";
    
    // append data
    file << name << "," << password << "," << balance << "\n";

    cout << "\nAccount registered successfully!";
    file.close();
}

void askInfo(){
    string name, password, verPassword;
    float balance = 0;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "\n***Password can include special characters and numbers. BUT NOT SPACES!***\n";
    cout << "Enter your desired password: ";
    cin >> password;

    // password verification
    cout << "\n***Password Verication***";
    while(verPassword != password){
        cout << "\nEnter your password again: ";
        cin >> verPassword;
        if(verPassword != password) cout << "\nPassword does not match!";
    }

    // save info
    registerAccount(name, password, balance);
}

bool verifyAccount(string name, string password){
    bool isFound = false;
    
    ifstream file("data.csv");
    if(!file.is_open()){
        cerr << "Failed to open file: data.csv";
    }

    string line;
    while(getline(file, line)){
        istringstream ss(line);
        string value1, value2;

        getline(ss, value1, ',');
        getline(ss, value2, ',');

        if(value1 == name && value2 == password){
            isFound = true;
            break;
        }
    }

    file.close();
    return isFound;
}

template <class data>
data selectChoice(string output, data limit){
    data choice;
    if(sizeof(limit) == sizeof(int)){
        do{
            cout << "\nEnter a " << output << "(1 - " << limit << "): ";
            cin >> choice;
            if(choice > limit || choice < 1){
                errorHandler(); 
                cout << "Invalid " << output << "!\n";
            }
        } while (choice > limit || choice < 1);
    } /*else {
        do{
            cout <<
            choice = toupper(choice);
        } while(choice != "Y" || choice != "N");
    }*/
    return choice;
}

int main(){
    int transaction;
    
    // run the system
    do{
        // welcome ui
        system("CLS");
        cout << "\nWelcome to JDL Bank!\n\n";
        drawUI(TRANSACTIONS);
        transaction = selectChoice<int>("transaction", 3);

        switch(transaction){
            case 1:
                // login ui
                system("CLS");
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your password: ";
                cin >> password;

                if(verifyAccount(name, password)){
                    cout << "Account existed!";
                } else{
                    cout << "\nAccount does not exist.\nPlease register first.";
                }
                
                Sleep(1500);
                break;
            case 2:
                // registration ui
                system("CLS");
                drawUI(REGISTRATION);
                askInfo();
                Sleep(1500);
                break;
            case 3:
                cout << "\n\nThank you customer! Please come back again :D";
                break;
        }
    } while(transaction != 3);
    return 0;
}
