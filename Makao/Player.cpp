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

int Player::MakeAMove(Stack * stack) {
	for (int i = 0; i < Hand.size(); i++)
	{
		if (CanBePut(stack->getTopCard(), *Hand[i], stack->getDrawStack(), stack->getDesiredSuit(), stack->getDesiredCard(), stack->getStopStack()))
		{
			if (stack->TryCards(Hand[i]))		//! Can only remove card from hand if TryCards returns true for them
				Hand.erase(Hand.begin() + i);
			return Hand.size();					//! Must return number of cards left in hand if not drawing
		}
	}

	return -1;	//! return -1 if you can't make a move or want to draw a card
}

Player::~Player() {
}
