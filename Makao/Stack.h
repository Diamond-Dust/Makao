#pragma once
#include "Card.h"
#include <vector>

class Stack {
	friend class Game;
	private:
		std::vector<Card*> BottomCards;
		int drawStack;
		cSuit desiredSuit;
		cRank desiredCard;
		int stopStack;
		Card TopCard;
		void Put(Card* next);
		void Put(std::vector<Card*> nexts);
		void clearDrawStack();
		void clearStopStack();
		std::vector<Card*> Clear();
		std::vector<Card*> RemoveBottom();
	public:
		Stack();
		Stack(Card* start);
		bool TryCards(Card* card);
		bool TryCards(std::vector<Card*> cards);
		cSuit getDesiredSuit();
		cRank getDesiredCard();
		int getDrawStack();
		Card getTopCard();
		int getStopStack();
		~Stack();
};