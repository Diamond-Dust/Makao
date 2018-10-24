#include "Validity.h"
#include "Cards.h"
#include <vector>
#include <algorithm>

bool CanBePut(Card first, Card next, std::vector<int> drawStack, cRank desiredCard, int stopStack) {
	if (stopStack != 0)
	{
		if (next.Rank != cRank::Four)
			return false;
		else
			return true;
	}
	else if (drawStack.empty())	//If there is no draw pending
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


