#ifndef CARDDECK_H
#define CARDDECK_H

// CardDeck represents a deck of cards stored as an array of integers.
// Cards are represented by values 0 through (size - 1).
class CardDeck {
public:
    CardDeck(int n = 52); //constructor

    //rule of three
    ~CardDeck(); 
    CardDeck(const CardDeck& other);
    CardDeck& operator = (const CardDeck& other);

    int getSize() const; 
    void shuffle();
    int deal(); //removes one card from the deck and returns its blackjack value
    
    void printDeck() const; //for part 1 shuffle test output

private: 
    int* cards; //dynamic array holding the deck
    int size; //current number of cards in deck

};

#endif
