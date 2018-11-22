#include "Card.h"

Card::Card() : Rank(cRank::Joker), Suit(cSuit::None) {
}

Card::Card(cRank rank, cSuit suit) : Rank(rank), Suit(suit) {
	if ((rank == cRank::Two) || (rank == cRank::Three) || 
		(rank == cRank::Four) || (rank == cRank::Valet) || 
		(rank == cRank::King) || (rank == cRank::Ace))
		Functional = true;
	else
		Functional = false;
}

void Card::Function(int& drawStack, cSuit & desiredSuit, cRank & desiredCard, int & stopStack) {
}

bool operator==(const Card& lhs, const Card& rhs) {
    return (unsigned int)lhs.Rank == (unsigned int)rhs.Rank;
}

bool operator!=(const Card& lhs, const Card& rhs) {
	return !(lhs == rhs);
}

Card::~Card() {

}
