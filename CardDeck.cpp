#include "CardDeck.h"
#include <iostream>
#include <cstdlib> //for rand()
using namespace std;

//builds a deck with values 0 to n-1
CardDeck::CardDeck(int n) {
    if (n <= 0) {
        n = 52;
    }

    size = n;
    cards = new int[size];

    for (int i = 0; i < size; i++) {
        cards[i] = i;
    }
}

//deconstructor releases the dynamic array
CardDeck::~CardDeck() {
    delete[] cards;
    cards = nullptr;
    size = 0;
}

//copy constructor replaces existing data with a deep copy
CardDeck::CardDeck(const CardDeck& other) {
    size = other.size;
    cards = new int[size];

    for (int i = 0; i < size; i++) {
        cards[i] = other.cards[i];
    }
}

//assignment operator replaces existing data with a deep copy
CardDeck& CardDeck::operator=(const CardDeck& other) {
    if (this == &other) return *this; //protect against self-assignment

    delete[] cards;

    size = other.size;
    cards = new int[size];

    for (int i = 0; i < size; i++) {
        cards[i] = other.cards[i];
    }

    return *this;
}

//returns current deck size
int CardDeck::getSize() const {
    return size;
}

//to shuffle without using srand and instead using rand, we can do a bunch of random swaps
// to mix up the order of the cards ensuring deterministic behavior for grading
void CardDeck::shuffle() {
    int i, j, temp;

    //does a bunch of random swaps
    for (int k = 0; k < size; k++) {
        i = rand() % size;
        j = rand() % size;

        temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

// Deals one card from the deck and converts it to a Blackjack value
int CardDeck::deal() {
    if (size == 0) {
        return -1; //indicate no cards left
    }

    int cardValue = cards[size - 1]; //get the last card's value
    size--; //reduce deck size

    //convert card value to blackjack value
    int rank = (cardValue % 13); //values 1-13
    int blackjackValue;
    
    if (rank == 0) {
        blackjackValue = 11; //ace is worth 11
    } else if (rank >= 10) {
        blackjackValue = 10; //face cards are worth 10
    } else {
        blackjackValue = rank + 1; //number cards are worth their value (1-10)
    }

    return blackjackValue;
}

void CardDeck::printDeck() const {
    for (int i = 0; i < size; i++) {
        cout << cards[i] << " ";
    }
    cout << endl;
}
