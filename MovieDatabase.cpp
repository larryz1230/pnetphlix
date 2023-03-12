#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


void seperate(string s, vector<string>&v){
    while (s.find(',')>0 && s.find(',')<s.size()){
        int temp  = s.find(',');
        v.push_back(s.substr(0, temp));
        s = s.substr(temp+1);
    }
    v.push_back(s);
}

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
    opened = false;
}

bool MovieDatabase::load(const string& filename)
{
    ifstream myFile(filename);
    
    if (!myFile.is_open()|| opened){
        return false;
    }
    
    string id;
    string name;
    string release;
    string temp_d;
    string temp_a;
    string temp_g;
    float rating;
    
    while (myFile.eof()==0) {
        vector<string> m_directors;
        vector<string> m_actors;
        vector<string> m_genres;
        getline(myFile, id);
        getline(myFile, name);
        getline(myFile, release);
        getline(myFile, temp_d);
        getline(myFile, temp_a);
        getline(myFile, temp_g);
        myFile >> rating;
        myFile.ignore(10000, '\n');
        
        seperate(temp_d, m_directors);
        seperate(temp_a, m_actors);
        seperate(temp_g, m_genres);
        
        Movie *m = new Movie(id, name, release, m_directors, m_actors, m_genres, rating);
        iddb.insert(id, m);
        for (string d: m_directors){
            directordb.insert(d, m);
        }
        for (string a: m_actors){
            actordb.insert(a, m);
        }
        for (string g: m_genres){
            genredb.insert(g, m);
        }
        
        getline(myFile, name);
        
    }
    myFile.close();
    opened = true;
    return true;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    if (iddb.find(id).is_valid()){
        return iddb.find(id).get_value();
    }
    else {
        return nullptr;
    }
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector <Movie*> v;
    TreeMultimap<string, Movie*>::Iterator it = directordb.find(director);
    if (it.is_valid()){
        while (it.is_valid()){
            v.push_back(it.get_value());
            it.advance();
        }
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector <Movie*> v;
    TreeMultimap<string, Movie*>::Iterator it = actordb.find(actor);
    if (it.is_valid()){
        while (it.is_valid()){
            v.push_back(it.get_value());
            it.advance();
        }
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector <Movie*> v;
    TreeMultimap<string, Movie*>::Iterator it = genredb.find(genre);
    if (it.is_valid()){
        while (it.is_valid()){
            v.push_back(it.get_value());
            it.advance();
        }
    }
    return v;
}
