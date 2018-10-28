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

void Ace::Function(std::vector<int>& drawStack, cSuit & desiredSuit, cRank & desiredCard, int & stopStack) {
	desiredSuit = this->desiredSuit;
}
