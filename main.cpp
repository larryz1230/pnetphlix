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

void findMatches(const Recommender& r,
const MovieDatabase& md,
const string& user_email,
int num_recommendations) {
vector<MovieAndRank> recommendations =
r.recommend_movies(user_email, num_recommendations);
    
    
if (recommendations.empty())
cout << "We found no movies to recommend :(.\n";
else {
for (int i = 0; i < recommendations.size(); i++) {
const MovieAndRank& mr = recommendations[i];
Movie* m = md.get_movie_from_id(mr.movie_id);
cout << i << ". " << m->get_title() << " ("
<< m->get_release_year() << ")\n Rating: "
<< m->get_rating() << "\n Compatibility Score: "
<< mr.compatibility_score << "\n";
}
}
}


auto start = chrono::steady_clock::now();


const string USER_DATAFILE  = "/Users/larryzhi/Desktop/cs32/p4/file.txt";


const string MOVIE_DATAFILE = "/Users/larryzhi/Desktop/cs32/p4/p4/movies.txt";

//const string USER_DATAFILE  = "users.txt";
//const string MOVIE_DATAFILE = "movies.txt";

//#include "treemm.h"

int main()
{

    UserDatabase udb;
       udb.load(USER_DATAFILE);
    
    auto stop = chrono::steady_clock::now();

    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;

       MovieDatabase mdb;
       mdb.load(MOVIE_DATAFILE);
    
    auto stop1 = chrono::steady_clock::now();

    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop1 - stop).count()) << "ms" << endl;

    Recommender recommender(udb, mdb);
    findMatches(recommender, mdb, "AndrA34840@juno.com", 10);

    
    
    auto stop2 = chrono::steady_clock::now();

    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop2- stop1).count()) << "ms" << endl;
    
    cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop2- start).count()) << "ms" << endl;
}


