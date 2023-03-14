#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    TreeMultimap<std::string, User*> userdb;    //create a treemap for users, to be searched with key id
    std::vector<User*> todeleteu;       //vector of pointers to delete in destructor
    bool opened;    //check if file has been opened
};

#endif // USERDATABASE_INCLUDED
