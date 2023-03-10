#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream> 


using namespace std;

UserDatabase::UserDatabase()
{
    opened = false;
    // Replace this line with correct code.
}

bool UserDatabase::load(const string& filename)
{

    ifstream myFile(filename);
    
    if (!myFile.is_open()|| opened){
        return false;
    }
    
    string text;
    string name;
    string email;
    int numids;
    vector<string> u_history;
    while (myFile) {
        getline(myFile, name);
        getline(myFile, email);
        myFile >> numids;
        myFile.ignore(100000, '\n');
        for (int i=0; i<numids; i++){
            getline(myFile, text);
            u_history.push_back(text);
        }
        getline(myFile, text);
        userdb.insert(email, new User(name, email, u_history));
    }
    myFile.close();
    opened = true;
    return true;  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (userdb.find(email).is_valid()){
        return userdb.find(email).get_value();
    }  // Replace this line with correct code.
    else {
        return nullptr;
    }
}
