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
		~Card();
};