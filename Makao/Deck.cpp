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
	if (Cards.size() == 0)
		return nullptr;
	Card* last = Cards.back();
	Cards.pop_back();
	return last;
}

std::vector<Card*> Deck::DrawCards(int number) {
	std::vector<Card*> cards;
	while (number--)
	{
		if (Cards.size() == 0)
			break;
		cards.push_back(Cards.back());
		Cards.pop_back();
	}
	return cards;
}

void Deck::ResetValetsAndAces() {
	for (int i = 0; i < Cards.size(); i++)
	{
		if (Cards[i]->Rank == cRank::Ace)
			static_cast<Ace*>(Cards[i])->setDesiredSuit(cSuit::None);
		else if (Cards[i]->Rank == cRank::Joker)
			static_cast<Valet*>(Cards[i])->setDesiredRank(cRank::Joker);
	}
}

void Deck::PutCards(Card * card) {
	int randomPlace = rand() % Cards.size();
	Card* swapper;
	swapper = Cards[randomPlace];
	Cards[randomPlace] = card;
	Cards.push_back(swapper);
}

void Deck::PutCards(std::vector<Card*> cards) {
	if (Cards.size() == 0)
	{
		Cards = cards;
	}
	else if (cards.size() == 1)
	{
		int randomPlace = rand() % Cards.size();
		Card* swapper;
		swapper = Cards[randomPlace];
		Cards[randomPlace] = cards[0];
		Cards.push_back(swapper);
	}
	else
	{
		std::random_shuffle(cards.begin(), cards.end());
		Cards.insert(std::begin(Cards), std::begin(cards), std::end(cards));
	}
}

void Deck::Shuffle() {
	std::random_shuffle(Cards.begin(), Cards.end());
}

int Deck::getCardNumber() {
	return Cards.size();
}

Deck::~Deck() {
	while (!Cards.empty())
	{
		delete Cards.back();
		Cards.pop_back();
	}
}
