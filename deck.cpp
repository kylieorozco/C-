#include "deck.h"
#include <cstdlib>
#include <ctime>

// create a standard 52-card deck
void Deck::createDeck() {
    deck.clear(); // Clear any existing cards
    for (int s = 1; s <= SUITSTYPE; s++) {
        for (Card::cPoints val = CARD_START; val < CARD_START + POINTS; val++) {
            Card::cSuits suit = s;
            Card newcard(suit, val);
            deck.push_back(newcard);
        }
    }
}

// shuffle the cards in 52-card deck
void Deck::shuffleDeck() {
    srand(time(0));
    Card temp;  // for swapping
    for (int i = deck.size() - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

// return a card from the tail of the deck
Card Deck::deal_a_card() {
    if (!deck.empty()) {
        Card topCard = deck.back();
        deck.pop_back();
        return topCard;
    } else {
        // If the deck is empty, return an invalid card
        return Card(); // Assuming Card() creates an invalid card
    }
}