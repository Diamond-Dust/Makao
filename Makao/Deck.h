#pragma once
#include "Card.h"
#include "FunctionalCards.h"
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Deck {
	private:
		const int cardNumber = 52;
		std::vector<Card*> Cards;
		//const int cardShortNumber = 24;
	public:
		Deck();
		Deck(int numOfDecks);
		int NumberOfDecks;
		Card* DrawCards();
		std::vector<Card*> DrawCards(int number);
		void Shuffle();
		~Deck();
};