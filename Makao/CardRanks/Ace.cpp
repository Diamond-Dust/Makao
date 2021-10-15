#include "Ace.h"

Ace::Ace() : Card(cRank::Ace, cSuit:: None) {
}

Ace::Ace(cSuit suit) : Card(cRank::Ace, suit){
	desiredSuit = cSuit::None;
}

void Ace::setDesiredSuit(cSuit suit) {
	if(suit != cSuit::COUNT && suit != cSuit::None)
		this->desiredSuit = suit;
}

cSuit Ace::getDesiredSuit()
{
	return this->desiredSuit;
}

void Ace::Function(int& drawStack, cSuit & desiredSuit, cRank & desiredCard, int & stopStack) {
	desiredSuit = this->desiredSuit;
	this->desiredSuit = cSuit::None;
}
