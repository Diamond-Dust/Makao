#pragma once
#include "CardRanks/Card.h"
#include "CardRanks/FunctionalCards.h"
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Deck {
	friend class Game;
	private:
		const int cardNumber = 52;
		std::vector<Card*> Cards;
		//const int cardShortNumber = 24;
		void PutCards(Card* card);
		void PutCards(std::vector<Card*> cards);
		std::vector<Card*> DrawCards(int number);
		void ResetValetsAndAces();
	public:
		Deck();
		Deck(int numOfDecks);
		const int NumberOfDecks;
		Card* DrawCards();
		void Shuffle();
		int getCardNumber();
		~Deck();
};