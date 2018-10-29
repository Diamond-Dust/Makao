#include "Player.h"

Player::Player() {
}

void Player::SetCards(std::vector<Card*> cards) {
	Hand = cards;
}

int Player::MakeAMove(Stack * stack, Deck * deck) {
	for (int i = 0; i < Hand.size(); i++)
	{
		if (CanBePut(stack->getTopCard(), *Hand[i], stack->getDrawStack(), stack->getDesiredSuit(), stack->getDesiredCard(), stack->getStopStack()))
		{
			if (stack->TryCards(Hand[i]))		//! Can only remove card from hand if TryCards returns true for them
				Hand.erase(Hand.begin() + i);
			return Hand.size();					//! Must return number of cards left in hand if not drawing
		}
	}

	Hand.push_back(deck->DrawCards());	//! Can only draw one card and must return -1 then
	return -1;
}

Player::~Player() {
}
