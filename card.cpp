#include "card.h"
#include <iostream>
#include <iomanip>
#include <string>

// Default constructor marks card as invalid
Card::Card() {
    suit = 0;
    point = 0;
}

// Alternate constructor
Card::Card(cSuits s, cPoints p) {
    suit = s;
    point = p;
}

// access the card point value
Card::cPoints Card::getPoint() const {
    return point;
}

// access the card suit value
Card::cSuits Card::getSuit() const {
    return suit;
}

// Overloading the less-than operator for Card class
// Returns true if the point of C1 is less than the point of C2
bool operator<(Card C1, Card C2) {
    return C1.point < C2.point;
}

// Overloading the insertion operator for Card class
// Display a description of the Card object to standard output
// The output should look like:
//   the sign of suit, followed by the point, then followed by the sign of suit again
ostream& operator<<(ostream& out, const Card& C) {
    int suitValue = C.suit;
    string pointChar;
    switch (C.point) {
        case 1:
            pointChar = "1";
            break;
        case 2:
            pointChar = "2";
            break;
        case 3:
            pointChar = "3";
            break;
        case 4:
            pointChar = "4";
            break;
        case 5:
            pointChar = "5";
            break;
        case 6:
            pointChar = "6";
            break;
        case 7:
            pointChar = "7";
            break;
        case 8:
            pointChar = "8";
            break;
        case 9:
            pointChar = "9";
            break;
        case 10:
            pointChar = "10";
            break;
        case 11:
            pointChar = "J";
            break;
        case 12:
            pointChar = "Q";
            break;
        case 13:
            pointChar = "K";
            break;
        case 14:
            pointChar = "A";
            break;
    }
    switch (suitValue) {
        case 1:
            out << CLUB << setw(2) << pointChar << CLUB;
            break;
        case 2:
            out << DIAMOND << setw(2) << pointChar << DIAMOND;
            break;
        case 3:
            out << HEART << setw(2) << pointChar << HEART;
            break;
        case 4:
            out << SPADE << setw(2) << pointChar << SPADE;
            break;
    }
    return out;
}

// Define a static function to compare two Card objects
// It returns true if C1.point is greater than or equal to C2.point
// Otherwise, returns false
bool Card::HigherBefore(const Card& C1, const Card& C2) {
    return C1.point >= C2.point;
}