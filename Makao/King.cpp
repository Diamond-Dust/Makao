#include "King.h"

King::King() : Card(cRank::King, cSuit::None) {

}

King::King(cSuit suit) : Card(cRank::King, suit) {

}

void King::Function(int& drawStack, cSuit & desiredSuit, cRank & desiredCard, int & stopStack) {
	if (this->Suit == cSuit::Hearts || this->Suit == cSuit::Spades)
		drawStack+=5;
}
