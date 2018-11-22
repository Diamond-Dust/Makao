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
		std::vector<int> absoluteStoppedPlayers;
		Card TopCard;
		void Put(Card* next);
		void Put(std::vector<Card*> nexts);
		void clearDrawStack();
		void clearStopStack();
		void setAbsoluteStoppedPlayer(int which);
		void decreaseAbsoluteStoppedPlayers(int number);
		void makeAbsoluteStoppedPlayers(int number);
		std::vector<Card*> Clear();
		std::vector<Card*> RemoveBottom();
		std::vector<int> getAbsoluteStoppedPlayers();
		int getAbsoluteStoppedPlayers(int which);
	public:
		Stack();
		Stack(Card* start);
		bool TryCards(Card* card);
		bool TryCards(std::vector<Card*> cards);
		cSuit getDesiredSuit() const;
		cRank getDesiredCard() const;
		int getDrawStack() const;
		Card getTopCard() const;
		int getStopStack() const;
		~Stack();
};