#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "User.h"
#include <unordered_map>

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;

};



class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    const UserDatabase* userdb;
    const MovieDatabase* moviedb;
    void mysort(std::unordered_map<std::string, int>& M, std::vector<MovieAndRank>& v, int num, std::vector<std::string> userw) const;
    struct ranking
    {
        ranking(std::string n, std::string a, int score, float b) : mr(a,score){
            name = n;
            rating = b;
        }
        MovieAndRank mr;
        float rating;
        std::string name;
    };
    
    static bool cmp(ranking& a, ranking& b);
};

#endif // RECOMMENDER_INCLUDED
