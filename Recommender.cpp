#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool cmp(pair<string, int>& a,
        pair<string, int>& b)
{
    return a.second > b.second;
}


void mysort(unordered_map<string, int>& M, vector<MovieAndRank>& v, int num, vector<string> userw)
{
 
    // Declare vector of pairs
    vector<pair<string, int> > A;
 
    // Copy key-value pair from Map
    // to vector of pairs
    
    
    for (auto& it : M) {
        bool canadd = true;
        for (int i=0; i<userw.size(); i++){
            if (it.first==userw.at(i)){
//                cout << "matches" << endl;
                canadd = false;
                break;
            }
            
        }
        if (canadd){
            A.push_back(it);
        }
//        canadd = true;
    }
 
    // Sort using comparator function
    sort(A.begin(), A.end(), cmp);
    
//    for (auto i = M.begin(); i != M.end(); i++)
//            cout << i->first << "     " << i->second
//                << endl;
    

 
//     Print the sorted value
    
//    for (auto& it : A) {
//
//        cout << it.first << ' '
//            << it.second << endl;
//    }
//
//    cout << "------------------" << endl;
//
//
    for (int i=0; i<num; i++){
        MovieAndRank temp(A.at(i).first, A.at(i).second);
        v.push_back(temp);
    }
//
//    for (auto& it : v) {
//
//            cout << it.movie_id << ' '
//                << it.compatibility_score << endl;
//    }
    
    
}


Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    // Replace this line with correct code.
    userdb = &user_database;
    moviedb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    
    //for each movie m in user
    //get directors list
    //for each director, each movie with the director +20
    //actor +30
    //genre +1
    
    User* user = userdb->get_user_from_email(user_email);
    
//    vector<MovieAndRank> vec;
    unordered_map <string, int> structset;
    
    if (user!=nullptr){
        
        for (int i=0; i<user->get_watch_history().size(); i++){
            string id = user->get_watch_history().at(i);
//            cout << "inserted" << endl;
            structset.insert(make_pair(id,-1));
//            if (id=="ID23628"){
//                cout << "DWDWEWEDEWDWE" << endl;
//            }
        }
        
        
        for (int i=0; i<user->get_watch_history().size(); i++){
            string id = user->get_watch_history().at(i);
//            cout << id << endl;
            Movie* m = moviedb->get_movie_from_id(id);
//            cout << m->get_title() << endl;
            for (int j=0; j<m->get_directors().size(); j++){
                
//                cout << m->get_directors().at(j) << endl;
//                cout <<moviedb->get_movies_with_director(m->get_directors().at(j)).size() <<endl;
                
                vector<Movie*> temp = moviedb->get_movies_with_director(m->get_directors().at(j));
                for (int k=0; k<temp.size(); k++){
                    
//                    cout << "at location " << structset[temp.at(k)->get_id()] << endl;
                    
                    if (structset.count(temp.at(k)->get_id())>0){
                        structset[temp.at(k)->get_id()] +=20;
//                        cout << "added" << endl;
                    }
                    else {
                        structset.insert(make_pair(temp.at(k)->get_id(), 20));
//                        cout << "inserted" << endl;
                    }
                }
            }
            for (int j=0; j<m->get_actors().size(); j++){
                vector<Movie*> temp = moviedb->get_movies_with_actor(m->get_actors().at(j));
                for (int k=0; k<temp.size(); k++){
                    
//                    cout << "at location " << structset[temp.at(k)->get_id()] << endl;
                    
                    if (structset.count(temp.at(k)->get_id())>0){
                        structset[temp.at(k)->get_id()] +=30;
//                        cout << "added" << endl;
                    }
                    else{
                        structset.insert(make_pair(temp.at(k)->get_id(), 30));
//                        cout << "inserted" << endl;
                    }
                }
            }
            for (int j=0; j<m->get_genres().size(); j++){
//                cout << m->get_genres().at(j) << endl;
//                cout <<moviedb->get_movies_with_genre(m->get_genres().at(j)).size() <<endl;

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
    
//    cout << structset.size() << endl;
    
    vector<MovieAndRank> toreturn;
    mysort(structset, toreturn, movie_count, user->get_watch_history());
   
    
//    for (auto i : structset){
//        cout << i.first << " \t\t\t " << i.second << endl;
//        MovieAndRank tempm(i.first, i.second) ;
//        toreturn.push_back(tempm);
//    }
    
    
    
    return toreturn;  // Replace this line with correct code.
}



