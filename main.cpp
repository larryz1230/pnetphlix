#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include <iostream>
#include <chrono>
#include <string>
#include "Recommender.h"
#include "treemm.h"
using namespace std;


auto start = chrono::steady_clock::now();


const string USER_DATAFILE  = "/Users/larryzhi/Desktop/cs32/p4/file.txt";


const string MOVIE_DATAFILE = "/Users/larryzhi/Desktop/cs32/p4/p4/movies.txt";

//const string USER_DATAFILE  = "users.txt";
//
//
//const string MOVIE_DATAFILE = "movies.txt";

//#include "treemm.h"

int main()
{
        
        UserDatabase udb;
        if (!udb.load(USER_DATAFILE))  // In skeleton, load always return false
        {
            cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
            return 1;
        }
    
        MovieDatabase mdb;
        mdb.load(MOVIE_DATAFILE);
        Recommender recommender(udb, mdb);
        for (;;)
        {
            cout << "Enter user email address (or quit): ";
            string email;
            getline(cin, email);
            if (email == "quit")
                return 0;
            User* u = udb.get_user_from_email(email);
            if (u == nullptr)
                cout << "No user in the database has that email address." << endl;
            else{
                vector<MovieAndRank> v = recommender.recommend_movies(email, 1000);
                    
                for (auto& it : v) {
            
                        cout << mdb.get_movie_from_id(it.movie_id)->get_title()  << ' '
                            << it.compatibility_score << ' ' << mdb.get_movie_from_id(it.movie_id)->get_rating()<< endl;
                }

            }
        }

    
//
//    UserDatabase udb;
//       udb.load(USER_DATAFILE);
//
//       MovieDatabase mdb;
//       mdb.load(MOVIE_DATAFILE);
//
//    Recommender recommender(udb, mdb);
//    vector<MovieAndRank> v = recommender.recommend_movies("AndrA34840@juno.com", 5);
//
//    for (auto& it : v) {
//
//            cout << it.movie_id << ' '
//                << it.compatibility_score << endl;
//    }
//
//
//    User* user = udb.get_user_from_email("AndrA34840@juno.com");


    
    auto stop = chrono::steady_clock::now();

    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
    
    
}
