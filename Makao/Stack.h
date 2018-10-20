#pragma once
#include "Card.h"
#include <vector>

class Stack {
	private:
		std::vector<Card> BottomCards;
		std::vector<int> drawStack;
	public:
		Stack();
		Card TopCard;
		bool PutCards(Card* card);
		bool PutCards(std::vector<Card*> cards);
		~Stack();
};