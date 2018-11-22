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

void Stack::setAbsoluteStoppedPlayer(int number) {
	absoluteStoppedPlayers[number] = stopStack-1;
}

void Stack::decreaseAbsoluteStoppedPlayers(int number) {
	absoluteStoppedPlayers[number]--;
}

void Stack::makeAbsoluteStoppedPlayers(int number) {
	for (int i = 0; i < number; i++)
		absoluteStoppedPlayers.push_back(0);
}

std::vector<Card*> Stack::Clear() {
	std::vector<Card*> cards = BottomCards;
	BottomCards.clear();
	desiredSuit = cSuit::None;
	desiredCard = cRank::Joker;
	TopCard = Card(cRank::Joker, cSuit::None);
	stopStack = 0;
	drawStack = 0;
	absoluteStoppedPlayers.clear();
	return cards;
}

std::vector<Card*> Stack::RemoveBottom() {
	Card* topCard = BottomCards.back();
	BottomCards.pop_back();
	std::vector<Card*> bottom = BottomCards;
	BottomCards.clear();
	BottomCards.push_back(topCard);
	return bottom;
}

std::vector<int> Stack::getAbsoluteStoppedPlayers() {
	return absoluteStoppedPlayers;
}

int Stack::getAbsoluteStoppedPlayers(int which) {
	return absoluteStoppedPlayers[which];
}

Stack::Stack() {
	desiredSuit = cSuit::None;
	desiredCard = cRank::Joker;
	TopCard = Card(cRank::Joker, cSuit::None);
	stopStack = 0;
	drawStack = 0;
}

Stack::Stack(Card * start) {
	desiredSuit = cSuit::None;
	desiredCard = cRank::Joker;
	TopCard = Card(cRank::Joker, cSuit::None);
	stopStack = 0;
	drawStack = 0;
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

	if (desiredCard != cRank::Joker && cards.size() > 1 && cards[0]->Rank != cRank::Valet)	//If more than one desired card is put on Valet
		return false;

	if (CanBePut(TopCard, *cards[0], drawStack, desiredSuit, desiredCard, stopStack))
	{
		Put(cards);
		return true;
	}
	else
		return false;
}

cSuit Stack::getDesiredSuit() const {
	return desiredSuit;
}

cRank Stack::getDesiredCard() const {
	return desiredCard;
}

int Stack::getDrawStack() const {
	return drawStack;
}

Card Stack::getTopCard() const {
	return TopCard;
}

int Stack::getStopStack() const {
	return stopStack;
}

Stack::~Stack() {
}
