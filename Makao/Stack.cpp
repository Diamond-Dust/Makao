#include "Stack.h"
#include "Validity.h"

void Stack::Put(Card * next) {
	next->Function(drawStack, desiredSuit, desiredCard, stopStack);
	BottomCards.push_back(next);
	TopCard = *BottomCards.back();
}

void Stack::Put(std::vector<Card*> nexts) {
	for (int i = 0; i < nexts.size(); i++)
		nexts[i]->Function(drawStack, desiredSuit, desiredCard, stopStack);
	BottomCards.insert(BottomCards.end(), nexts.begin(), nexts.end());
	TopCard = *BottomCards.back();
}

void Stack::clearDrawStack() {
	drawStack = 0;
}

void Stack::clearStopStack() {
	stopStack = 0;
}

std::vector<Card*> Stack::RemoveBottom() {
	Card* topCard = BottomCards.back();
	BottomCards.clear();
	std::vector<Card*> bottom = BottomCards;
	BottomCards.push_back(topCard);
	return bottom;
}

Stack::Stack() {
	desiredSuit = cSuit::None;
	desiredCard = cRank::Joker;
	stopStack = 0;
}

Stack::Stack(Card * start) {
	desiredSuit = cSuit::None;
	desiredCard = cRank::Joker;
	stopStack = 0;
	BottomCards.push_back(start);
	TopCard = *BottomCards.back();
}

bool Stack::TryCards(Card * card) {
	if (CanBePut(TopCard, *card, drawStack, desiredSuit, desiredCard, stopStack))
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

	if (CanBePut(TopCard, *cards[0], drawStack, desiredSuit, desiredCard, stopStack))
	{
		Put(cards);
		return true;
	}
	else
		return false;
}

cSuit Stack::getDesiredSuit() {
	return desiredSuit;
}

cRank Stack::getDesiredCard() {
	return desiredCard;
}

int Stack::getDrawStack() {
	return drawStack;
}

Card Stack::getTopCard() {
	return TopCard;
}

int Stack::getStopStack() {
	return stopStack;
}

Stack::~Stack() {
}
