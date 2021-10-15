#include "Player.h"

Player::Player() {
}

void Player::DrawCard(Card * card) {
	Hand.push_back(card);
}

void Player::DrawCard(std::vector<Card*> cards) {
	Hand.insert(Hand.end(), cards.begin(), cards.end());
}

void Player::SetCards(std::vector<Card*> cards) {
	Hand = cards;
}

std::vector<Card*> Player::MakeAMove(const Stack * stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops) {
	std::vector<Card*> thrownCards;

	for (int i = 0; i < Hand.size(); i++)
	{
		if (CanBePut(stack->getTopCard(), *Hand[i], stack->getDrawStack(), stack->getDesiredSuit(), stack->getDesiredCard(), stack->getStopStack()))
		{
			thrownCards.push_back(Hand[i]);
			Hand.erase(Hand.begin() + i);
			break;
		}
	}

	return thrownCards;
}

int Player::getCardNumber() {
	return Hand.size();
}

Player::~Player() {
}
