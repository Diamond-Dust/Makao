#include "AgaBot.h"
#include "WindowsBenchmarking.h"

bool AgaBot::End(std::vector<Card*>& pCards, std::vector<Card*>& toThrow) {
	cRank currentRank;
	if (pCards.size())
		currentRank = pCards[0]->Rank;
	else
		currentRank = Hand[0]->Rank;
	for (int i = 1; i < pCards.size(); i++)
		if (pCards[i]->Rank != currentRank)
			return false;
	for (int i = 0; i < Hand.size(); i++)
		if (Hand[i]->Rank != currentRank)
			return false;
	if(pCards.size())
	{
		Hand.insert(Hand.end(), pCards.begin(), pCards.end());
		toThrow.insert(toThrow.begin(), Hand.begin(), Hand.end());
		Hand.clear();
		return true;
	}
	return false;
}

std::vector<cSuit> AgaBot::SumBySuit() {
	for (int i = 0; i < (int)cSuit::COUNT; i++)
		sums[i] = 0;
	for (int i = 0; i < Hand.size(); i++)
		++sums[(int)Hand[i]->Suit];

	int maxIndex;
	for (int j = 0; j < (int)cSuit::COUNT; j++) 
	{
		maxIndex = 0;
		for (int i = 0; i < sums.size(); i++)
		{
			if (sums[maxIndex] < sums[i])
			{
				maxIndex = i;
			}
		}
		suits[j] = (cSuit)(maxIndex);
		sums[maxIndex] = 0;
	}
		
	return suits;
}

int AgaBot::SumFours() {
	int result = 0;
	for (int i = 0; i < Hand.size(); i++)
		if (Hand[i]->Rank == cRank::Four)
			++result;
	return result;
}

int AgaBot::SumDraws() {
	int result = 0;
	for (int i = 0; i < Hand.size(); i++)
		if (IsDraw(*Hand[i]))
			++result;
	return result;
}

int AgaBot::SumRanks() {
	std::vector<int> ranks((int)cRank::COUNT, 0);
	for (int i = 0; i < Hand.size(); i++)
		++ranks[(int)Hand[i]->Rank];
	int result = 0;
	for (int i = 0; i < (int)cRank::COUNT; i++)
		if (ranks[i])
			++result;
	return result;
}

AgaBot::AgaBot() : suits((int)cSuit::COUNT), sums((int)cSuit::COUNT, 0) {
	ValetChain.first = false;
	ValetChain.second = cRank::Joker;
	AceChain.first = false;
	AceChain.second = cSuit::None;
}

std::vector<Card*> AgaBot::MakeAMove(const Stack * stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops) {
	std::vector<Card*> thrownCards;
	
	suits = SumBySuit();

	int fourSum = SumFours();
	int drawSum = SumDraws();
	
	if (ValetChain.first)	//If chaining
	{
		Card* chosenValet;
		int valetIndex;
		ValetChain.first = false;
		for (int i = 0; i < Hand.size(); i++)
		{
			if (Hand[i]->Rank == ValetChain.second)	//There is another to chain
			{
				ValetChain.first = true;
			}
			else if (Hand[i]->Rank == cRank::Valet)	//There is another Valet
			{
				chosenValet = Hand[i];
				valetIndex = i;

			}
		}
		if (ValetChain.first)
		{
			Hand.erase(Hand.begin() + valetIndex);
			static_cast<Valet*>(chosenValet)->setDesiredRank(ValetChain.second);
			thrownCards.push_back(chosenValet);
		}
		return thrownCards;
	}

	std::vector<Card*> puttableCards;		//Needs to be put back inside the hand if not thrown
	for (int i = 0; i < Hand.size(); i++)
	{
		if (CanBePut(stack, *Hand[i]))
		{
			puttableCards.push_back(Hand[i]);
			Hand.erase(Hand.begin() + i);
		}
	}

	/* Sounds good, doesn't work
	//Thanks to mzal for showing me this
	auto cmp = [&](const Card* &a, const Card* &b)->bool { 
		for (int i = 0; i < suits.size(); i++)
		{
			if (suits[i] == a->Suit)
				return true;
			if (suits[i] == b->Suit)
				return false;
		} 
		return false; 
	};

	std::sort(puttableCards.begin(), puttableCards.end(), cmp);	//Sort by colour sums
	*/

	for (int i = 0; i + 1 < puttableCards.size(); i++)
	{
		for (int j = 1; j + i < puttableCards.size(); j++)
		{
			for (int k = 0; k < suits.size(); k++)
			{
				if (suits[k] == puttableCards[j]->Suit)
					break;
				if (suits[k] == puttableCards[j - 1]->Suit)
				{
					Card* swap = puttableCards[j];
					puttableCards[j] = puttableCards[j - 1];
					puttableCards[j - 1] = swap;
				}
			}
		}
	}

	if (End(puttableCards, thrownCards))	//Puts everything in thrown if it can
		return thrownCards;

	if (AceChain.first)	//If chaining
	{
		AceChain.first = false;
		for (int i = 0; i < puttableCards.size(); i++)
		{
			if (puttableCards[i]->Rank == cRank::Ace)	//There is another Ace
			{
				AceChain.first = true;
				static_cast<Ace*>(puttableCards[i])->setDesiredSuit(AceChain.second);
				thrownCards.push_back(puttableCards[i]);
				puttableCards.erase(puttableCards.begin() + i);
			}
		}
		return thrownCards;
	}

	cRank currentRank = cRank::Joker;
	int nextPlayerCards = 0;
	for (int i = 0; i < otherPlayersCards.size(); i++)
		nextPlayerCards = !nextPlayerCards ? otherPlayersCards[i] : nextPlayerCards;

	for (int i = 0; i < puttableCards.size(); i++)	//Put first card
	{
		if (puttableCards[i]->Rank == cRank::Four)
		{
			if (!stack->getStopStack() && fourSum < 2)	//If no four is necessary and has only one
				continue;
			else
			{
				currentRank = puttableCards[i]->Rank;
				thrownCards.push_back(puttableCards[i]);
				puttableCards.erase(puttableCards.begin() + i);
				break;
			}
		}
		else if (IsDraw(*puttableCards[i]))
		{
			if (nextPlayerCards >= 5 && drawSum < 3)
				continue;
			else
			{
				currentRank = puttableCards[i]->Rank;
				thrownCards.push_back(puttableCards[i]);
				puttableCards.erase(puttableCards.begin() + i);
				break;
			}
		}
		else
		{
			currentRank = puttableCards[i]->Rank;
			thrownCards.push_back(puttableCards[i]);
			puttableCards.erase(puttableCards.begin() + i);
			break;
		}
	}

	if (!thrownCards.empty() && thrownCards[0]->Rank != cRank::Valet && thrownCards[0]->Rank != cRank::Ace)
	{
		for (int i = 0; i < Hand.size(); i++)	//Put more cards of the same rank, last one is the most popular
		{
			if (Hand[i]->Rank == currentRank)
			{
				for (int j = 0; j < (int)cSuit::COUNT; j++)
				{
					if (Hand[i]->Suit == suits[j])
					{
						thrownCards.push_back(Hand[i]);
						break;
					}
					else if (thrownCards.back()->Suit == suits[j])
					{
						thrownCards.insert(thrownCards.begin(), Hand[i]);
						break;
					}
				}
				Hand.erase(Hand.begin() + i);
			}
		}
	}
	else if (!thrownCards.empty() && thrownCards[0]->Rank != cRank::Ace) //If Ace
	{
		AceChain.first = true;
		AceChain.second = suits[0];
		static_cast<Ace*>(thrownCards.back())->setDesiredSuit(suits[0]);
	}
	else if (!thrownCards.empty() && thrownCards[0]->Rank != cRank::Ace) //If Valet
	{
		cRank chosenRank;
		for (int i = 0; i < Hand.size(); i++)
		{
			if (Hand[i]->Suit == suits[0])
				chosenRank = Hand[i]->Rank;
		}
		for (int i = 0; i < puttableCards.size(); i++)
		{
			if (Hand[i]->Suit == suits[0])
				chosenRank = Hand[i]->Rank;
		}
		ValetChain.first = true;
		ValetChain.second = chosenRank;
		static_cast<Valet*>(thrownCards[0])->setDesiredRank(chosenRank);
	}		

	Hand.insert(Hand.end(), puttableCards.begin(), puttableCards.end());
	
	return thrownCards;
}

AgaBot::~AgaBot() {
}
