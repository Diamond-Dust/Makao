#include "Stack.h"
#include "Validity.h"

void Stack::Put(Card * next) {
	BottomCards.push_back(next);
	TopCard = *BottomCards.back();
}

void Stack::Put(std::vector<Card*> nexts) {
	BottomCards.insert(BottomCards.end(), nexts.begin(), nexts.end());
	TopCard = *BottomCards.back();
}

Stack::Stack() {
	desiredCard = cRank::Joker;
	stopStack = 0;
}

Stack::Stack(Card * start) {
	desiredCard = cRank::Joker;
	stopStack = 0;
	BottomCards.push_back(start);
	TopCard = *BottomCards.back();
}

bool Stack::TryCards(Card * card) {
	if (CanBePut(TopCard, *card, drawStack, desiredCard, stopStack))
	{
		Put(card);
		return true;
	}
	else
		return false;
}

bool Stack::TryCards(std::vector<Card*> cards) {
	for (int i = 1; i < cards.size(); i++)
	{
		if (cards[i]->Rank != cards[i - 1]->Rank)
			return false;
	}

	if (CanBePut(TopCard, *cards[0], drawStack, desiredCard, stopStack))
	{
		Put(cards);
		return true;
	}
	else
		return false;
}

cRank Stack::getDesiredCard() {
	return desiredCard;
}

std::vector<int> Stack::getDrawStack() {
	return std::vector<int>(drawStack);
}

Card Stack::getTopCard() {
	return TopCard;
}

int Stack::getStopStack() {
	return stopStack;
}

Stack::~Stack() {
}
