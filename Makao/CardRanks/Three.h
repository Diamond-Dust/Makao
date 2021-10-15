#pragma once
#include "Card.h"
#include <vector>

class Three : public Card {
	public:
		Three();
		Three(cSuit suit);
		void Function(int& drawStack, cSuit& desiredSuit, cRank& desiredCard, int& stopStack);
};