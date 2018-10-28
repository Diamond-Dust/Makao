#pragma once
#include "Card.h"
#include <vector>

class Four : public Card {
	public:
		Four();
		Four(cSuit suit);
		void Function(std::vector<int> drawStack, cSuit& desiredSuit, cRank& desiredCard, int& stopStack);
};