#include "Valet.h"

Valet::Valet() : Card(cRank::Valet, cSuit::None) {
	desiredRank = cRank::Joker;
}

Valet::Valet(cSuit suit) : Card(cRank::Valet, suit) {
	desiredRank = cRank::Joker;
}

void Valet::setDesiredRank(cRank rank) {
	if (!((rank == cRank::Two) || (rank == cRank::Three) ||
		(rank == cRank::Four) || (rank == cRank::Valet) ||
		(rank == cRank::King) || (rank == cRank::Ace) || rank == cRank::COUNT))
		desiredRank = rank;
}

void Valet::Function(std::vector<int> drawStack, cSuit & desiredSuit, cRank & desiredCard, int & stopStack) {
	desiredCard = desiredRank;
}
