#include "Deck.h"

Deck::Deck() : NumberOfDecks(1) {
	for (int i = 0; i < (int)cRank::COUNT; i++)
	{
		for (int j = 0; j < (int)cSuit::COUNT; j++)
		{
			switch ((cRank)i) {
				case cRank::Two:
					Cards.push_back(new Two((cSuit)j));
					break;
				case cRank::Three:
					Cards.push_back(new Three((cSuit)j));
					break;
				case cRank::Four:
					Cards.push_back(new Four((cSuit)j));
					break;
				case cRank::Valet:
					Cards.push_back(new Valet((cSuit)j));
					break;
				case cRank::King:
					Cards.push_back(new King((cSuit)j));
					break;
				case cRank::Ace:
					Cards.push_back(new Ace((cSuit)j));
					break;
				default:
					Cards.push_back(new Card((cRank)i, (cSuit)j));
					break;
			}
		}
	}
}

Deck::Deck(int numOfDecks) : NumberOfDecks(numOfDecks) {
	for (int k = 0; k < numOfDecks; k++)
	{
		for (int i = 0; i < (int)cRank::COUNT; i++)
		{
			for (int j = 0; j < (int)cSuit::COUNT; j++)
			{
				switch ((cRank)i) {
				case cRank::Two:
					Cards.push_back(new Two((cSuit)j));
					break;
				case cRank::Three:
					Cards.push_back(new Three((cSuit)j));
					break;
				case cRank::Four:
					Cards.push_back(new Four((cSuit)j));
					break;
				case cRank::Valet:
					Cards.push_back(new Valet((cSuit)j));
					break;
				case cRank::King:
					Cards.push_back(new King((cSuit)j));
					break;
				case cRank::Ace:
					Cards.push_back(new Ace((cSuit)j));
					break;
				default:
					Cards.push_back(new Card((cRank)i, (cSuit)j));
					break;
				}
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
		cards.push_back(Cards.back());
		Cards.pop_back();
	}
	return cards;
}

void Deck::Shuffle() {
	std::srand(unsigned(std::time(0)));
	std::random_shuffle(Cards.begin(), Cards.end());
}

Deck::~Deck() {
	while (!Cards.empty())
	{
		delete Cards.back();
		Cards.pop_back();
	}
}
