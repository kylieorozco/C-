/*
 * Course: CS216-00x
 * Project: Lab8 Part 2 (as part of Project 2)
 * Purpose: use the Card and Deck classes to display 
 *          the 5 cards in user's hand in descreasing order by card points
 *          Note the suit of a card has NO impact on the order
 *          A (=14) has higher point than all other cards, J = 11, Q = 12, K = 13
 *          1 point is not used in the card 
*/
#include <iostream>
#include <algorithm>    //use std::sort() function
#include "card.h"
#include "deck.h"

using namespace std ;

int main() 
{
    // Avoid magic numbers
    const int HANDS = 5;    // play 5 in hand
    
    // create an object of Deck class to represent standard 52-card deck
    // create a 52-card deck first
    // then shuffle the cards
    Deck playDeck;
    playDeck.createDeck();
    playDeck.shuffleDeck();

    Card fiveCards[HANDS];
    cout << "The cards in your hand are: "<< endl;

    for (int i=0; i< HANDS; i++)
    {    
        fiveCards[i] = playDeck.deal_a_card();
        cout << fiveCards[i] << "\t";
    }
    
    cout << endl << endl << "The cards in your hand are put in order: " << endl;
    vector<Card> sortedCards(HANDS);
    for (int i =0; i < HANDS; i++)
        sortedCards.at(i) =fiveCards[i];
    // sort the sequence of cards in descreasing order by card points
    // using the function HigherBefore to define the sorting criterion 
    std::sort(sortedCards.begin(), sortedCards.end(), Card::HigherBefore);
    for (int i=0; i < HANDS; i++)
    {
        cout << sortedCards[i] << "\t";
    }
    cout << endl;
    return 0;
}

