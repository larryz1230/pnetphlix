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

UserDatabase::~UserDatabase()
{
    for (User* u : todeleteu){
        delete u;
    }
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
    string num;
    int numids;
    while (myFile) {
        vector<string> u_history;
        getline(myFile, name);
        getline(myFile, email);
//        myFile >> numids;
//        myFile.ignore(10000, '\n');
        getline(myFile, num);
        numids = stoi(num);
        for (int i=0; i<numids; i++){
            getline(myFile, text);
            u_history.push_back(text);
        }
        getline(myFile, text);
        User* temp = new User(name, email, u_history);
        userdb.insert(email, temp);
        todeleteu.push_back(temp);
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
