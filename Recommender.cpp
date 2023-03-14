#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool Recommender::cmp(ranking& a,  //compares two ranking structs and returns if a is larger than b
        ranking& b)
{
    if (a.mr.compatibility_score==b.mr.compatibility_score){
        if (a.rating==b.rating){
            return a.name < b.name;
        }
        return a.rating>b.rating;
    }
    return a.mr.compatibility_score > b.mr.compatibility_score;
}


void Recommender::mysort(unordered_map<string, int>& M, vector<MovieAndRank>& v, int num, vector<string> userw) const
{
    vector<ranking> A;      //temp vector of rankings
    for (auto& it : M) {
        bool canadd = true;
        for (int i=0; i<userw.size(); i++){     //if not already watched by the user
            if (it.first==userw.at(i)){
                canadd = false;
                break;
            }
            
        }
        if (canadd){    //create a ranking and push it in vector A
            MovieAndRank temp(it.first, it.second);
            ranking temp1(moviedb->get_movie_from_id(it.first)->get_title(), it.first, it.second,    moviedb->get_movie_from_id(temp.movie_id)->get_rating());
            A.push_back(temp1);
        }
    }
 
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    for (int i=0; i<num && i<A.size(); i++){        //loop through number of outputs
        if (A.at(i).mr.compatibility_score==0){     //if we hit 0, don't return any more recommendations
            return;
        }
        MovieAndRank temp(A.at(i).mr.movie_id, A.at(i).mr.compatibility_score);     //create temp struct
        v.push_back(temp);  //push back results vector, which is referenced
    }
    
}

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    //constructor
    userdb = &user_database;
    moviedb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    //get user
    User* user = userdb->get_user_from_email(user_email);
    unordered_map <string, int> moviemap;
    if (user!=nullptr){
        for (int i=0; i<user->get_watch_history().size(); i++){     //loop through each movie
            string id = user->get_watch_history().at(i);
            Movie* m = moviedb->get_movie_from_id(id);
            
            for (int j=0; j<m->get_directors().size(); j++){        //for each director in the movie
                vector<Movie*> temp = moviedb->get_movies_with_director(m->get_directors().at(j));
                for (int k=0; k<temp.size(); k++){      //find all movies by this director
                    if (moviemap.count(temp.at(k)->get_id())>0){    //insert into unordered map
                        moviemap[temp.at(k)->get_id()] +=20;
                    }
                    else {
                        moviemap.insert(make_pair(temp.at(k)->get_id(), 20));
                    }
                }
            }
            for (int j=0; j<m->get_actors().size(); j++){       //repeat for actors
                vector<Movie*> temp = moviedb->get_movies_with_actor(m->get_actors().at(j));
                for (int k=0; k<temp.size(); k++){

                    if (moviemap.count(temp.at(k)->get_id())>0){
                        moviemap[temp.at(k)->get_id()] +=30;

                    }
                    else{
                        moviemap.insert(make_pair(temp.at(k)->get_id(), 30));

                    }
                }
            }
            for (int j=0; j<m->get_genres().size(); j++){       //repeat for genres
                vector<Movie*> temp = moviedb->get_movies_with_genre(m->get_genres().at(j));
                for (int k=0; k<temp.size(); k++){
                    if (moviemap.count(temp.at(k)->get_id())>0){
                        moviemap[temp.at(k)->get_id()] +=1;
                    }
                    else{
                        moviemap.insert(make_pair(temp.at(k)->get_id(), 1));
                    }
                }
            }
        }
    }
    

    vector<MovieAndRank> toreturn;      //create vector to return results
    mysort(moviemap, toreturn, movie_count, user->get_watch_history());     //sort vector with top n number of recs
    
    return toreturn;        //return
}



