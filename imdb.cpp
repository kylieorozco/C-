/*
 * File: imdb.cpp
 * Course: CS216-00
 * Project: Project 1
 * Purpose: Provide the implementation of the class named IMDB
 *          This class represents a movie-actor database
 */
#include <regex>  // needs c++11 standard
#include "imdb.h"

using namespace std;

// default constructor
IMDB::IMDB()
{
    //do nothing
    //since map class contains a default contructor
    //      which constructs an empty container, with no elements
}

   // insert a pair<actorName, the set of movieTitle of this actor>
void IMDB::insert_an_actor(string actorName, set<string> movieTitles)
{
    // First upgrade actors_db
    // if the key actorName does not exist
    //        add the key to the map actors_db
    
    if(actors_db.count(actorName)==1){ // key actorName exists
        actors_db[actorName]=movieTitles;
    }else{
        actors_db.insert({actorName, movieTitles}); // actorName doesnt exist
    }


    // Second upgrade movies_db
    // for each movieTitle in the set of movieTitles,
    // insert actorName to its actors set


    for(auto movies:movieTitles){ // iterate all movies in movieTitles
        movies_db[movies].insert(actorName); // insert actorName to relevant movie
    }


}

// use passing in parameter, movieTitle, as the pattern to match 
// one existing movie in the map
// return the matched movie title from the map
// otherwise return empty string
string IMDB::matchExistingMovie(string movieTitle) const
{
    string matchedMovie;
    bool found = false;
    // generate the regular expression to match 
    // which contains movieTitle as a substring
    // note that it performs case insensitive matching
    regex reg(movieTitle, regex_constants::icase);
    auto it = movies_db.begin();
    while (!found && it != movies_db.end())
    {
        if (regex_search(it->first, reg))
        {
            found = true;
            matchedMovie = it->first;
        }
        else
            it++;
    }
    return matchedMovie;
}

// check if a movieTitle does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingMovie(const string& userInput) const
{
    // Convert user input to lowercase and remove leading/trailing whitespace
    string userInputLower = userInput;
    transform(userInputLower.begin(), userInputLower.end(), userInputLower.begin(), ::tolower);
    userInputLower.erase(0, userInputLower.find_first_not_of(" \t\n\r\f\v"));
    userInputLower.erase(userInputLower.find_last_not_of(" \t\n\r\f\v") + 1);

    // Iterate through movies_db to find a match
    for (const auto& entry : movies_db) {
        // Convert the stored movie title to lowercase and remove leading/trailing whitespace
        string storedTitle = entry.first;
        transform(storedTitle.begin(), storedTitle.end(), storedTitle.begin(), ::tolower);
        storedTitle.erase(0, storedTitle.find_first_not_of(" \t\n\r\f\v"));
        storedTitle.erase(storedTitle.find_last_not_of(" \t\n\r\f\v") + 1);

        // Check if the user input matches any part of the movie title
        if (storedTitle.find(userInputLower) != string::npos) {
            return true; // Found a match
        }
    }
    return false; // No match found
}

// check if an actorName does exist in the map
// return true if it does; otherwise return false
bool IMDB::isExistingActor(string actorName) const
{
    for (const auto& movieEntry : movies_db){ //iterate movieEntry in movies_db
        if (movieEntry.second.find(actorName) != movieEntry.second.end()){ //if find actorName in movieEntry, 
            return true;
        }
    }
    return false;
}

// return a set of movie titles which actorName is in
// if the passing in parameter: actorName, is not in the database, 
//                   display message and return an empty set
set<string> IMDB::find_movies_for_an_actor(string actorName) const
{
   set<string> result;
   //actorIt iterator to entry in actors_db
   auto actorIt = actors_db.find(actorName); 
   // check if actorName exists in actors_db
   if (actorIt != actors_db.end()){ 
    // actor found, return the set of movies
        result = actorIt->second;
   } else { 
    // actor not found, empty set and display message
        cout << "Actor" << actorName << " not found in the database." << endl;
   }
   return result;
}

// return a set of actor names which are all in the movieTitle
// if the passing in parameter: movieTitle is not in the database, 
//                   display message and return an empty set
set<string> IMDB::find_actors_in_a_movie(string movieTitle) const
{
    set<string> result;

    // check if the movieTitle exists in movies_db
    auto movieIt = movies_db.find(movieTitle);
    if (movieIt != movies_db.end()) {
        // movie found, return the set of actor names
        result = movieIt->second;
    } else {
        // movie not found, display message and return an empty set
        cout << "Movie " << movieTitle << " not found in the database." << endl;
    }
    return result;
}

set<string> IMDB::find_common_actors(const string& movie1, const string& movie2) const {
    set<string> common_actors;
    auto actors_in_movie1 = movies_db.find(movie1);
    auto actors_in_movie2 = movies_db.find(movie2);

    if (actors_in_movie1 != movies_db.end() && actors_in_movie2 != movies_db.end()) {
        for (const auto& actor : actors_in_movie1->second) {
            if (actors_in_movie2->second.find(actor) != actors_in_movie2->second.end()) {
                common_actors.insert(actor);
            }
        }
    }
    return common_actors;
}

// Return the set of actors appearing in only one of the two movies
set<string> IMDB::find_unique_actors(const string& movie1, const string& movie2) const {
    set<string> unique_actors;
    auto actors_in_movie1 = movies_db.find(movie1);
    auto actors_in_movie2 = movies_db.find(movie2);

    if (actors_in_movie1 != movies_db.end() && actors_in_movie2 != movies_db.end()) {
        for (const auto& actor : actors_in_movie1->second) {
            if (actors_in_movie2->second.find(actor) == actors_in_movie2->second.end()) {
                unique_actors.insert(actor);
            }
        }
        for (const auto& actor : actors_in_movie2->second) {
            if (actors_in_movie1->second.find(actor) == actors_in_movie1->second.end()) {
                unique_actors.insert(actor);
            }
        }
    }
    return unique_actors;
}

// Return the set of actors appearing in a specific movie
set<string> IMDB::find_actors_in_movie(const string& movieTitle) const {
    set<string> actors;
    auto it = movies_db.find(movieTitle);
    if (it != movies_db.end()) {
        actors = it->second;
    }
    return actors;
}

// Definition of analyzeCoActors method
void IMDB::analyzeCoActors() const {
    std::map<std::string, std::set<std::string>> coActorsMap;

    // Iterate through each actor in the actors database
    for (const auto& actorEntry : actors_db) {
        const std::string& actorName = actorEntry.first;
        const std::set<std::string>& movies = actorEntry.second;

        // Iterate through each movie the actor appeared in
        for (const auto& movie : movies) {
            // Find all actors in the same movie
            std::set<std::string> coActorsInMovie = find_actors_in_a_movie(movie);
            
            // Remove the current actor from the set
            coActorsInMovie.erase(actorName);
            
            // Add the co-actors to the map
            coActorsMap[actorName].insert(coActorsInMovie.begin(), coActorsInMovie.end());
        }
    }

    // Print the co-actors for each actor
    for (const auto& entry : coActorsMap) {
        const std::string& actorName = entry.first;
        const std::set<std::string>& coActors = entry.second;

        std::cout << "Co-actors for " << actorName << ": ";
        for (const auto& coActor : coActors) {
            std::cout << coActor << ", ";
        }
        std::cout << std::endl;
    }
}

const map<string, set<string>>& IMDB::getActorsDB() const {
    return actors_db;
}