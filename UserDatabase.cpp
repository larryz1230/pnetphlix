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
}

UserDatabase::~UserDatabase()
{
    for (User* u : todeleteu){      //for each pointer created, delete
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
    while (myFile) {            //loop through and store data in new User objects
        vector<string> u_history;
        getline(myFile, name);
        getline(myFile, email);
        getline(myFile, num);
        numids = stoi(num);
        for (int i=0; i<numids; i++){
            getline(myFile, text);
            u_history.push_back(text);
        }
        getline(myFile, text);
        User* temp = new User(name, email, u_history);      //create new User object from info
        userdb.insert(email, temp);     //insert object into treemultimap
        todeleteu.push_back(temp);      //add to deletion vector
    }
    myFile.close();
    opened = true;
    return true;  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const      //returns user given an email key
{
    if (userdb.find(email).is_valid()){     //calls multimaps function, get iterator
        return userdb.find(email).get_value();
    }  
    else {
        return nullptr;
    }
}
