#pragma once
#include <initializer_list>
#include "Cards.h"

class Card {
	public:
		Card();
		Card(cRank rank, cSuit suit);
		cRank Rank;
		cSuit Suit;
		bool Functional;
		void Function(std::vector<int> drawStack, cSuit& desiredSuit, cRank& desiredCard, int& stopStack) = 0;
		~Card();
};