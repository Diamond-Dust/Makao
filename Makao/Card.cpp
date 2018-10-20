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

Card::~Card() {

}
