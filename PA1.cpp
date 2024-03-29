#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <map>
#include <sstream>
#include "imdb.h"
#include <algorithm>

/*
 * Course: CS216-00x
 * Project: Project 1
 * Purpose: it reads data from an input file which passes as command line argument
 *          then stores in an object of IMDB class (to represent imdb database)
 *          two movies are from the user-input, then performs case insensitive matching
 *          and match the movie titles from the database
 *          it then allowes the user to input an actor/actress name, to search for co-actors in each movie which this actor/actress was in, in a well-formatted display
 * Author: Kylie Orozco
 */

using namespace std;

void analyzeCoActors(const IMDB& imdb){
    imdb.analyzeCoActors();
}

int main(int argc, char* argv[])
{
    const int COMM_NUM = 1;
    // Check whether the number of command line arguments is exactly one 
    if (argc != COMM_NUM + 1)
    {
        cout << "Warning: need exactly " << COMM_NUM << " command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }
    
    ifstream in_file;
    in_file.open(argv[COMM_NUM]);

    // Check whether the input file can be open successfully or not
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[COMM_NUM] << "!" << endl;
        return 2;
    }

    // Read data from the input file, assume "good data" from the input file
    // each line of the input file: actor name; movie1; movie2; ...; movieN;
    // read one line at a time then tokenize it:
    // create a pair <actor_name, the set of movieTitles which the actor was in>
    //        and insert to IMDB object
    IMDB cs216_imdb;

    while (!in_file.eof())
    {
        string line;
        getline(in_file, line);
        string actorName, movieTitle;
        // check if the text line is not empty then tokenize it
        if (line.length() != 0)
        {
            istringstream iss(line);
            getline(iss, actorName,';');
            // Extract extra white space
            iss>>ws;

            // Create a new set of movies associated with name
            set<string> movies;

            while (getline(iss, movieTitle, ';'))
            {
                // Remove leading and trailing whitespace from movie title
                movieTitle.erase(0, movieTitle.find_first_not_of(" \t\n\r\f\v"));
                movieTitle.erase(movieTitle.find_last_not_of(" \t\n\r\f\v") + 1);
                
                movies.insert(movieTitle);
                // extract white space 
                iss>>ws;
            }
            // insert the pair to IMDB object: cs216_imdb
            cs216_imdb.insert_an_actor(actorName, movies);
        }
    }
    // close the input file
    in_file.close();

    while (true)
    {
        cout << "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. Actors in Movies" << endl;
        cout << "2. Actors and co-actors" << endl;

        // Get the option from the user
        char choice;
        cin >> choice;
        if (toupper(choice) == 'Q')
            break;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Process the option
        switch (choice)
        {
        case '1': {
            string movie1, movie2;
            // Ask the user to input the titles of two movies
            cout << "Please input the first movie title: ";
            getline(cin >> ws, movie1);
            cout << "Please input the second movie title: ";
            getline(cin >> ws, movie2);

            transform(movie1.begin(), movie1.end(), movie1.begin(), ::tolower);
            transform(movie2.begin(), movie2.end(), movie2.begin(), ::tolower);

            // Check if both movie titles are valid
            // Find the actual movie titles in the database based on user input
            string matchedMovie1 = cs216_imdb.matchExistingMovie(movie1);
            string matchedMovie2 = cs216_imdb.matchExistingMovie(movie2);

            // Check if both movie titles are valid
            bool validMovie1 = !matchedMovie1.empty();
            bool validMovie2 = !matchedMovie2.empty();

            // Print the matched movie titles
            if (validMovie1 && validMovie2) {
                cout << "Your input matches the following two movies:" << endl;
                cout << "1. " << matchedMovie1 << endl;
                cout << "2. " << matchedMovie2 << endl;
                cout << "Both movies are in the database, please continue..." << endl;
            } else {
                cout << "At least one of the movie titles is invalid." << endl;
                continue;
            }

            // Show the menu options
            bool validChoice;
            do {
                validChoice = true;
                cout << "Please input your menu option (enter Q or q to quit):" << endl;
                cout << "A. Print all the actors in either of the two movies." << endl;
                cout << "C. Print all the common actors in both movies." << endl;
                cout << "O. Print all the actors who are in only one movie, but not in both." << endl;

                char sub_option;
                cin >> sub_option;

                // Clear input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (toupper(sub_option)) {
                    case 'A': {
                        // Print all the actors in either of the two movies
                        set<string> actors1 = cs216_imdb.find_actors_in_a_movie(matchedMovie1);
                        set<string> actors2 = cs216_imdb.find_actors_in_a_movie(matchedMovie2);
                        cout << "All the actors in either of the two movies:" << endl;
                        for (const auto& actor : actors1)
                            cout << actor << endl;
                        for (const auto& actor : actors2)
                            cout << actor << endl;
                        break;
                    }
                    case 'C': {
                        // Print all the common actors in both movies
                        set<string> common_actors = cs216_imdb.find_common_actors(matchedMovie1, matchedMovie2);
                        cout << "Common actors in " << matchedMovie1 << " and " << matchedMovie2 << ": " << endl;
                        for (const auto& actor : common_actors)
                            cout << actor << endl;
                        break;
                    }
                    case 'O': {
                        // Print all the actors who are in only one movie
                        set<string> unique_actors = cs216_imdb.find_unique_actors(matchedMovie1, matchedMovie2);
                        cout << "Actors in " << matchedMovie1 << " but not in " << matchedMovie2 << ": " << endl;
                        for (const auto& actor : unique_actors)
                            cout << actor << endl;
                        cout << "Actors in " << matchedMovie2 << " but not in " << matchedMovie1 << ": " << endl;
                        set<string> actors1 = cs216_imdb.find_actors_in_movie(matchedMovie1);
                        set<string> actors2 = cs216_imdb.find_actors_in_movie(matchedMovie2);
                        for (const auto& actor : actors2)
                            if (actors1.find(actor) == actors1.end())
                                cout << actor << endl;
                        break;
                    }
                    case 'Q': {
                        break;
                    }
                    default:
                        cout << "Invalid option!" << endl;
                        validChoice = false;
                }
            } while (!validChoice);
            break;
        }
        case '2': {
            analyzeCoActors(cs216_imdb);
            break;
        }
        default:
            cout << "Invalid option number!" << endl;
        }
    }
    return 0;
}