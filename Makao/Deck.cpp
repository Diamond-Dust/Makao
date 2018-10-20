#include "Deck.h"

Deck::Deck() : NumberOfDecks(1) {
	for (int i = 0; i < (int)cSuit::COUNT; i++)
	{
		for (int j = 0; j < (int)cRank::COUNT; j++)
		{
			Cards.push_back(new Card((cRank)j, (cSuit)i));
		}
	}
}

Deck::Deck(int numOfDecks) : NumberOfDecks(numOfDecks) {
	for (int i = 0; i < (int)cSuit::COUNT; i++)
	{
		for (int j = 0; j < (int)cRank::COUNT; j++)
		{
			for (int k = 0; k < numOfDecks; k++)
			{
				Cards.push_back(new Card((cRank)j, (cSuit)i));
			}
		}
	}
}

Card * Deck::DrawCards() {
	Card* last = Cards.back();
	return last;
}

std::vector<Card*> Deck::DrawCards(int number) {
	std::vector<Card*> cards;
	while (number--)
	{
		Cards.push_back(Cards.back());
		Cards.pop_back();
	}
	return cards;
}

void Deck::Shuffle() {
	std::srand(unsigned(std::time(0)));
	std::random_shuffle(&Cards[0], &Cards[cardNumber*NumberOfDecks]);
}

Deck::~Deck() {
	while (!Cards.empty())
	{
		delete Cards.back();
		Cards.pop_back();
	}
}
