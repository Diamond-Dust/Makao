#pragma once
#include "Card.h"
#include <vector>

class Stack {
	private:
		std::vector<Card*> BottomCards;
		std::vector<int> drawStack;
		cRank desiredCard;
		int stopStack;
		Card TopCard;
		void Put(Card* next);
		void Put(std::vector<Card*> nexts);
	public:
		Stack();
		Stack(Card* start);
		bool TryCards(Card* card);
		bool TryCards(std::vector<Card*> cards);
		cRank getDesiredCard();
		std::vector<int> getDrawStack();
		Card getTopCard();
		int getStopStack();
		~Stack();
};