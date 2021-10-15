#pragma once
#include <initializer_list>
#include <vector>
#include "../Cards.h"

class Card {
	public:
		Card();
		Card(cRank rank, cSuit suit);
		cRank Rank;
		cSuit Suit;
		bool Functional;
		virtual void Function(int& drawStack, cSuit& desiredSuit, cRank& desiredCard, int& stopStack);
		~Card();
};