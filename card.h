/* File: card.h
 * Course: CS216-00x
 * Project: Lab 8 (as part of Project 2)
 * Purpose: the declaration for the Card class.
 */

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <map>
using namespace std;

// define the unicode for four suits for display purpose
const string SPADE = "\e[0;30;47m\xe2\x99\xa0\e[0;37;40m";
const string CLUB = "\e[0;30;47m\xe2\x99\xa3\e[0;37;40m";
const string HEART = "\e[0;31;47m\xe2\x99\xa5\e[0;37;40m";
const string DIAMOND = "\e[0;31;47m\xe2\x99\xa6\e[0;37;40m";

// define the map for four suits 
static const map<int, const string> SUITS = {{0, "Invalid"},{1, CLUB},{2,DIAMOND}, {3, HEART}, {4, SPADE}};

class Card 
{
    public:
        // Type definition for the suit value of a playing card.
        // 0: "Invalid", 1: CLUB, 2: DIAMOND, 3: HEART, 4: SPADE
        // Note: outside Card member functions, refer this type using Card::cSuits
        typedef unsigned int cSuits;

        // Type definition for the point value of a playing card.
        // A point value of 0 means the Card object has not been initialized.
        // J = 11, Q = 12, K = 13, A = 14.
        // A point value of 1 is not used.
        // Note: outside Card member functions, refer this type using Card::cPoints
        //
        typedef unsigned int cPoints;

        // Default constructor.
        // We allow uninitialized Cards to be created.
        // This allows arrays of Cards.
        // Uninitialized cards should have 0(Invalid) for its suit
        // and 0 for its points.
        Card(); 

        // Alternate constructor
        // Create a Card with specified suit and points.
        Card(cSuits s, cPoints p);

        // access the card point value
        cPoints getPoint() const;

        // access the card suit value
        cSuits getSuit() const;

        // define the operator "<" for Card class
        // C1 < C2 if and only if the point of C1 is less than the point of C2 
        friend bool operator<(Card C1, Card C2);

        // define the operator "<<" for Card class
        // directly send the Card object to the cout, in the following format:
        //   the sign of suit, followed by the point, then followed by the sign of suit again
        friend ostream& operator<<(ostream& out, const Card& C);

        // define a static function to compare two Card objects
        // it returns true if C1.point is greater than or equal to C2.point
        // otherwise, returns false
        static bool HigherBefore(const Card& C1, const Card& C2);

    private:
        cSuits suit;        // suit of the card
        cPoints point;    // point value of the card
};
#endif  /* CARD_H */
