#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <iostream>
#include <string>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";


//const string MOVIE_DATAFILE = "movies.txt";
//
//int main()
//{
//	UserDatabase udb;
//	if (0&&!udb.load(USER_DATAFILE))  // In skeleton, load always return false
//	{
//		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
//		return 1;
//	}
//	for (;;)
//	{
//		cout << "Enter user email address (or quit): ";
//		string email;
//		getline(cin, email);
//		if (email == "quit")
//			return 0;
//		User* u = udb.get_user_from_email(email);
//		if (u == nullptr)
//			cout << "No user in the database has that email address." << endl;
//		else
//			cout << "Found " << u->get_full_name() << endl;
//	}
//}
//

#include "treemm.h"

int main()
{
    
    UserDatabase udb;
    udb.load("/Users/larryzhi/Desktop/cs32/p4/file.txt");
    
    MovieDatabase mdb;
    mdb.load("/Users/larryzhi/Desktop/cs32/p4/p4/mmmo.txt");
    
//    Movie* m = mdb.get_movie_from_id("ID38613");
//    cout << m->get_title() << endl;
    
    vector<Movie*> dd = mdb.get_movies_with_actor("Perry Miller Adato");
    for (int i=0; i<dd.size(); i++){
        cout << dd[i]->get_title() << endl;
    }
    
    
//    User* user = udb.get_user_from_email("AbFow2483@charter.net");
//    cout << user->get_full_name() << endl;
//    for (int i=0; i<user->get_watch_history().size(); i++){
//        cout << user->get_watch_history()[i] << endl;
//    }
    
    
    
    
//    TreeMultimap<int, string> tmap;
//
//    tmap.insert(2, "hello");
//    tmap.insert(1, "few");
//    tmap.insert(3, "hellefo");
//    tmap.insert(5, "adlo");
//    tmap.insert(3, "adcwceo");
//    tmap.insert(2, "fewf");
//
//
//    tmap.find(2);
//    TreeMultimap<int, string> :: Iterator it = tmap.find(3);
//
//
//
//    while (it.is_valid()){
//        cout << it.get_value()<<endl;
//        it.advance();
//    }
////
//    cout << "_________________" << endl;
//    tmap.printTree();
}
