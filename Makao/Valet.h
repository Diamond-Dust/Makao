#pragma once
#include "Card.h"
#include <vector>

class Valet : public Card {
	private:
		cRank desiredRank;
	public:
		Valet();
		Valet(cSuit suit);
		void setDesiredRank(cRank rank);
		void Function(std::vector<int> drawStack, cSuit& desiredSuit, cRank& desiredCard, int& stopStack);
};