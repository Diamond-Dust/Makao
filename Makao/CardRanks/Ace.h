#pragma once
#include "Card.h"
#include <vector>

class Ace : public Card {
	private:
		cSuit desiredSuit;
	public:
		Ace();
		Ace(cSuit suit);
		void setDesiredSuit(cSuit suit);
		cSuit getDesiredSuit();
		void Function(int& drawStack, cSuit& desiredSuit, cRank& desiredCard, int& stopStack);
};