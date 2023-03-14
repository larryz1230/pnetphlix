
#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
    TreeMultimap<std::string, Movie*> actordb;      //treemap to search by actor key
    TreeMultimap<std::string, Movie*> directordb;   //treemap to search by director key
    TreeMultimap<std::string, Movie*> genredb;  //treemap to search by genre key
    TreeMultimap<std::string, Movie*> iddb; //treemap to search by id key, returns only 1
    
    std::vector<Movie*> todeletem;      //deletion vector for destructor
    bool opened;      //check if file has been opened
};

#endif // MOVIEDATABASE_INCLUDED
