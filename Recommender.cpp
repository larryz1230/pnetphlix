#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//struct ranking{
//
//};



bool Recommender::cmp(ranking& a,  //add secondary comps
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
 
    vector<ranking> A;

    for (auto& it : M) {
        bool canadd = true;
        for (int i=0; i<userw.size(); i++){
            if (it.first==userw.at(i)){
                canadd = false;
                break;
            }
            
        }
        if (canadd){
            MovieAndRank temp(it.first, it.second);
            ranking temp1(moviedb->get_movie_from_id(it.first)->get_title(), it.first, it.second, moviedb->get_movie_from_id(temp.movie_id)->get_rating());
            A.push_back(temp1);
        }
    }
    
//    cout << A.size() << endl;
 
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);

    for (int i=0; i<num && i<A.size(); i++){
        if (A.at(i).mr.compatibility_score==0){
            return;
        }
        MovieAndRank temp(A.at(i).mr.movie_id, A.at(i).mr.compatibility_score);
        v.push_back(temp);
    }
    
}


Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{

    userdb = &user_database;
    moviedb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    
    User* user = userdb->get_user_from_email(user_email);
    
//    vector<MovieAndRank> vec;
    unordered_map <string, int> structset;
    
    if (user!=nullptr){
        
        for (int i=0; i<user->get_watch_history().size(); i++){
            string id = user->get_watch_history().at(i);

            Movie* m = moviedb->get_movie_from_id(id);

            for (int j=0; j<m->get_directors().size(); j++){
                
                
                
                vector<Movie*> temp = moviedb->get_movies_with_director(m->get_directors().at(j));
                for (int k=0; k<temp.size(); k++){
                    
                    
                    if (structset.count(temp.at(k)->get_id())>0){
                        structset[temp.at(k)->get_id()] +=20;
                    }
                    else {
                        structset.insert(make_pair(temp.at(k)->get_id(), 20));

                    }
                }
            }
            for (int j=0; j<m->get_actors().size(); j++){
                vector<Movie*> temp = moviedb->get_movies_with_actor(m->get_actors().at(j));
                for (int k=0; k<temp.size(); k++){

                    if (structset.count(temp.at(k)->get_id())>0){
                        structset[temp.at(k)->get_id()] +=30;

                    }
                    else{
                        structset.insert(make_pair(temp.at(k)->get_id(), 30));

                    }
                }
            }
            for (int j=0; j<m->get_genres().size(); j++){


                vector<Movie*> temp = moviedb->get_movies_with_genre(m->get_genres().at(j));
                for (int k=0; k<temp.size(); k++){

                    //                    cout << "at location " << structset[temp.at(k)->get_id()] << endl;

                    if (structset.count(temp.at(k)->get_id())>0){
                        structset[temp.at(k)->get_id()] +=1;
//                        cout << "added" << endl;
                    }
                    else{

                        structset.insert(make_pair(temp.at(k)->get_id(), 1));
                        //                        cout << "inserted" << endl;
                    }
                }
            }
        }
    }
    

    vector<MovieAndRank> toreturn;
    mysort(structset, toreturn, movie_count, user->get_watch_history());
    
    return toreturn;  // Replace this line with correct code.
}



