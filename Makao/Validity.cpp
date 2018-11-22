#include "Validity.h"
#include "Cards.h"
#include <vector>
#include <algorithm>

bool CanBePut(Card first, Card next, int drawStack, cSuit desiredSuit, cRank desiredCard, int stopStack) {
	if (first.Rank == cRank::Joker)
		return true;
	else if (stopStack != 0)
	{
		if (next.Rank != cRank::Four)
			return false;
		else
			return true;
	}
	else if (drawStack == 0)	//If there is no draw pending
	{
		if (desiredCard != cRank::Joker)	//if Valet was played
		{
			if (first.Rank == cRank::Valet)	//if Valet is still on top
			{
				if ((next.Rank == cRank::Valet) || (next.Rank == desiredCard))	//If tested card is a Valet or desired
					return true;
				else
					return false;
			}
			else
			{
				if (next.Rank == desiredCard)	//If tested card is desired
					return true;
				else
					return false;
			}
		}
		else if (desiredSuit != cSuit::None)
		{
			if ((next.Rank == cRank::Ace) || (next.Suit == desiredSuit))	//If card matches
				return true;
			else
				return false;
		}
		else
		{
			if ((next.Rank == first.Rank) || (next.Suit == first.Suit))	//If card matches
				return true;
			else
				return false;
		}
	}
	else
	{
		if ((next.Rank == cRank::Two) || (next.Rank == cRank::Three) ||
			(next.Rank == cRank::King && ((next.Suit == cSuit::Hearts) ||
				(next.Suit == cSuit::Spades))))
		{
			if ((next.Rank == first.Rank) || (next.Suit == first.Suit))	//If card matches
				return true;
			else
				return false;
		}
		else
			return false;
	}

}

bool CanBePut(const Stack* stack, Card next) {
	return CanBePut(stack->getTopCard(), next, stack->getDrawStack(), stack->getDesiredSuit(), stack->getDesiredCard(), stack->getStopStack());
}

bool IsFunctional(cRank rank) {
	return ((rank == cRank::Two) || (rank == cRank::Three) || (rank == cRank::Four) || (rank == cRank::Valet) || (rank == cRank::King));
}

bool IsDraw(Card card) {
	return (card.Rank == cRank::Two || card.Rank == cRank::Three || (card.Rank == cRank::King && (card.Suit == cSuit::Hearts || card.Suit == cSuit::Spades)));
}


