#pragma once
#include "Card.h"
#include <vector>

class King : public Card {
	public:
		King();
		King(cSuit suit);
		void Function(std::vector<int>& drawStack, cSuit& desiredSuit, cRank& desiredCard, int& stopStack);
};