// main.cpp
// Tests CardDeck functionality and runs a simplified Blackjack game
#include <iostream>
#include "CardDeck.h"   // class definition for CardDeck used below
using namespace std;

void resetDeckIfNeeded(CardDeck* &deck) {
    if (deck->getSize() < 15) { //if deck is low on cards, delete and create a new shuffled deck
        delete deck;
        deck = new CardDeck();
        deck->shuffle();
    }
}

int main() {
  // Required test: verify shuffle works on a small deck
  CardDeck test(10);

  cout << "Deck before shuffle: ";
  test.printDeck();

  test.shuffle();

  cout << "Deck after shuffle: ";
  test.printDeck();

  // Required Rule of Three test: copy constructor and assignment operator
  CardDeck a(10);
  CardDeck b = a;
  CardDeck c(20);
  c = b;

  // Begin Blackjack gameplay using a dynamically allocated deck
  CardDeck *deck = new CardDeck(); //create a full deck
  deck->shuffle(); //shuffle the deck

  //keep track of wins for player and dealer across multiple games
  int playerWins = 0;
  int dealerWins = 0;
  int ties = 0;

  char playAgain = 'y';
  while (playAgain == 'y') {
  
    //player and dealer totals start at 0 and get updated as cards are dealt
    int playerTotal = 0;
    int dealerTotal = 0;

    //both player and dealer get dealt two cards to start
    resetDeckIfNeeded(deck); // Ensure enough cards remain before dealing
    playerTotal += deck->deal();

    resetDeckIfNeeded(deck);
    playerTotal += deck->deal();

    resetDeckIfNeeded(deck);
    dealerTotal += deck->deal();
    
    resetDeckIfNeeded(deck);
    dealerTotal += deck->deal();

    cout << "Player total: " << playerTotal << endl;
    cout << "Dealer shows: " << dealerTotal << endl;

    char choice; //player's turn and input for hit or stand

    while (playerTotal < 21) {
        cout << "Do you want to hit or stand? (h/s): ";
        cin >> choice;

        if (choice == 'h') {
          resetDeckIfNeeded(deck);
          playerTotal += deck->deal();
          cout << "Player total: " << playerTotal << endl;
        } else if (choice == 's') {
          break;
        } else {
          cout << "Invalid choice. Please enter 'h' or 's'." << endl;
        }
    }

    //if player busts game ends immediately and the deck gets deleted
    if (playerTotal > 21) {
      cout << "Player busts! Dealer wins." << endl;
      dealerWins++;
    } else {
      while (dealerTotal < 17) { //dealer must hit until they have at least 17
        cout << "Dealer hits." << endl;
        resetDeckIfNeeded(deck);
        dealerTotal += deck->deal();
      }
      cout << "Dealer total: " << dealerTotal << endl;

      if (dealerTotal > 21) {
          cout << "Dealer busts! Player wins." << endl;
          playerWins++;
      } else if (dealerTotal > playerTotal) {
          cout << "Dealer wins!" << endl;
          dealerWins++;
      } else if (dealerTotal < playerTotal) {
          cout << "Player wins!" << endl;
          playerWins++;
      } else {
          cout << "It's a tie!" << endl;
          ties++;
      }
    }

    cout << "Play again? (y/n): ";
    cin >> playAgain;
    //check for invalid input for play again prompt
    while (playAgain != 'y' && playAgain != 'n') {
      cout << "Invalid choice. Please enter 'y' or 'n'." << endl;
      cout << "Play again? (y/n): ";
      cin >> playAgain;
    }
  }

  //final score output after player is done playing includes ties
  cout << "Score - Player: " << playerWins << " Dealer: " << dealerWins << " Ties: " << ties << endl;
  delete deck; //clean up dynamic memory
  return 0;
}
