#include "User.h"

#include <string>
#include <vector>
using namespace std;

//constructor
User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    this->full_name = full_name;
    this->email = email;
    this->watch_history = watch_history;
}

//accessors
string User::get_full_name() const
{
    return full_name;
}

string User::get_email() const
{
    return email;
}

vector<string> User::get_watch_history() const
{
    return watch_history;
}
