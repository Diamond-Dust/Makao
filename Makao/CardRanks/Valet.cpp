#include "Valet.h"

Valet::Valet() : Card(cRank::Valet, cSuit::None) {
	this->desiredRank = cRank::Joker;
}

Valet::Valet(cSuit suit) : Card(cRank::Valet, suit) {
	this->desiredRank = cRank::Joker;
}

void Valet::setDesiredRank(cRank rank) {
	if (!((rank == cRank::Two) || (rank == cRank::Three) || (rank == cRank::Four) || (rank == cRank::Valet) || (rank == cRank::King) || (rank == cRank::Ace) || (rank == cRank::COUNT)))
		this->desiredRank = rank;
}

cRank Valet::getDesiredRank()
{
	return this->desiredRank;
}

void Valet::Function(int& drawStack, cSuit & desiredSuit, cRank & desiredCard, int & stopStack) {
	desiredCard = this->desiredRank;
	this->desiredRank = cRank::Joker;
}
