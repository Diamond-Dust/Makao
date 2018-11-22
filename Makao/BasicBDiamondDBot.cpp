#include "BasicBDiamondDBot.h"

std::vector<CardStack> BasicBDiamondDBot::StackHand() {
	std::vector<CardStack> cStack;

	for (int i = 0; i < (int)cRank::COUNT; i++)
		cStack.push_back(makeCardStack(0, i));

	for (int i = 0; i < Hand.size(); i++)
	{
		++cStack[(int)Hand[i]->Rank].num;
		cStack[(int)Hand[i]->Rank].col[(int)Hand[i]->Suit] = true;
	}
		
	return cStack;
}

std::vector<CardStack> BasicBDiamondDBot::PutCheckCardStack(std::vector<CardStack> cStack, const Stack* stack)
{
	for (int i = 0; i < (int)cRank::COUNT; i++)
	{
		if (cStack[i].num != 0)
		{
			for (int j = 0; j < (int)cSuit::COUNT; j++)
			{
				if (cStack[i].col[j])
				{
					if (CanBePut(stack->getTopCard(), Card(cStack[i].type, (cSuit)j), stack->getDrawStack(), stack->getDesiredSuit(), stack->getDesiredCard(), stack->getStopStack()))
					{
						cStack[i].canPut = true;
					}
				}
			}
		}
	}
	return cStack;
}

std::vector<CardStack> BasicBDiamondDBot::sortCardStack(std::vector<CardStack> cStack) {
	std::sort(cStack.begin(), cStack.end(), compareCardStacks);
	return cStack;
}

bool BasicBDiamondDBot::CheckValetChain(const Stack* stack, std::vector<Card*>& toThrow, std::vector<CardStack>& cStack) {
	if (ValetChain.first && ValetChain.second != cRank::Joker)	//Check if chain is running
	{
		if (cStack[(int)cRank::Valet].num == 1)	//No Valets, end chain
		{
			ValetChain.first = false;
			ValetChain.second = cRank::Joker;
		}

		for (int i = 0; i < Hand.size(); i++)
		{
			if (Hand[i]->Rank != cRank::Valet)
				continue;
			if (CanBePut(stack, *Hand[i]))
			{
				((Valet*)Hand[i])->setDesiredRank(ValetChain.second);
				toThrow.push_back(Hand[i]);
				Hand.erase(Hand.begin() + i);
				return true;
			}
		}
	}
	else if (!IsFunctional(cStack[0].type))	//Check if you can use Valet
	{
		if (cStack[(int)cRank::Valet].num > 0)
		{
			if (cStack[(int)cRank::Valet].num > 1)	//If Valet chain can be executed
				ValetChain.first = true;
			if (cStack[(int)cRank::Valet].canPut)
			{
				for (int i = 0; i < Hand.size(); i++)
				{
					if (Hand[i]->Rank != cRank::Valet)
						continue;
					if (CanBePut(stack, *Hand[i]))
					{
						ValetChain.second = cStack[0].type;
						((Valet*)Hand[i])->setDesiredRank(cStack[0].type);
						toThrow.push_back(Hand[i]);
						Hand.erase(Hand.begin() + i);
						return true;
					}
				}
			}
		}
		else
			ValetChain.first = false;
	}
	return false;
}

bool BasicBDiamondDBot::CheckKingCombo(const Stack * stack, std::vector<Card*>& toThrow, std::vector<CardStack>& cStack) {
	for (int i = 0; i < (int)cRank::COUNT; i++)	//Check for King combos
	{
		if (cStack[i].canPut)
		{
			if (cStack[i].type == cRank::King)
			{
				for (int j = 0; j < Hand.size(); j++)
				{
					if (Hand[j]->Rank != cRank::King)
						continue;
					if (CanBePut(stack, *Hand[j]) && (Hand[j]->Suit == cSuit::Hearts || Hand[j]->Suit == cSuit::Spades))
					{
						for (int k = 0; k < (int)cRank::COUNT; k++)
						{
							if (cStack[k].type == cRank::Two && cStack[k].col[(int)Hand[j]->Suit])
							{
								toThrow.push_back(Hand[j]);
								Hand.erase(Hand.begin() + j);
								return true;
							}
						}
					}
				}
			}
		}
		else
			break;
	}
	return false;
}

bool BasicBDiamondDBot::CheckTwoThreePlay(int nextPlayerCards, const Stack * stack, std::vector<Card*>& toThrow, CardStack * two, CardStack * three) {
	if (!two->canPut && !three->canPut)	//Can't play
		return false;
	else if (two->num + three->num < 2 && Hand.size() > 3)	//Save them
		return false;
	else
	{
		if (two->num + three->num < nextPlayerCards / 5)	//Risky attack
			return false;
		else
		{
			if (two->num * 2 > three->num * 3)
			{
				for (int i = 0; i < Hand.size(); i++)
				{
					if (Hand[i]->Rank != cRank::Two)
						continue;
					if (CanBePut(stack, *Hand[i]))
					{
						toThrow.push_back(Hand[i]);
						Hand.erase(Hand.begin() + i);
					}
				}
			}
			else
			{
				for (int i = 0; i < Hand.size(); i++)
				{
					if (Hand[i]->Rank != cRank::Three)
						continue;
					if (CanBePut(stack, *Hand[i]))
					{
						toThrow.push_back(Hand[i]);
						Hand.erase(Hand.begin() + i);
					}
				}
			}

			return true;
		}
	}
}

bool BasicBDiamondDBot::CheckDrawCards(int nextPlayerCards, const Stack * stack, std::vector<Card*>& toThrow, std::vector<CardStack>& cStack) {
	if(CheckKingCombo(stack, toThrow, cStack))
		return true;

	CardStack* two, *three;

	for (int i = 0; i < (int)cRank::COUNT; i++)	//Get throwable draw cards
	{
		if (cStack[i].type == cRank::Two)
			two = &(cStack[i]);
		else if (cStack[i].type == cRank::Three)
			three = &(cStack[i]);
	}

	if (CheckTwoThreePlay(nextPlayerCards, stack, toThrow, two, three))
		return true;
	return false;
}

BasicBDiamondDBot::BasicBDiamondDBot() : Player() {
	ValetChain.first = false;
	ValetChain.second = cRank::Joker;
}

std::vector<Card*> BasicBDiamondDBot::MakeAMove(const Stack * stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops) {
	std::vector<Card*> thrownCards;

	std::vector<CardStack> cStack = sortCardStack(PutCheckCardStack(StackHand(), stack));	//Sort into type stacks and sort check if you can play them

	if(CheckValetChain(stack, thrownCards, cStack))
		return thrownCards;

	{
		int nextPlayerCards = 0;
		for (int i = 0; i < otherPlayersCards.size(); i++)
			nextPlayerCards = !nextPlayerCards ? otherPlayersCards[i] : nextPlayerCards;
		if (CheckDrawCards(nextPlayerCards, stack, thrownCards, cStack))
			return thrownCards;
	}

	for (int i = 0; i < Hand.size(); i++)
	{
		if (Hand[i]->Rank == cStack[0].type)
		{
			if (Hand[i]->Rank == cRank::Valet)	//clear Valets
				((Valet*)Hand[i])->setDesiredRank(cRank::Joker);

			if (CanBePut(stack, *Hand[i]))
			{
				thrownCards.insert(thrownCards.begin(), Hand[i]);
			}
			else
			{
				thrownCards.push_back(Hand[i]);
			}
			Hand.erase(Hand.begin() + i);
		}
	}



	return thrownCards;
}

CardStack makeCardStack(int a, cRank b) {
	CardStack cS = { false, a,{ false, false, false, false }, b };
	return cS;
}

CardStack makeCardStack(int a, int b) {
	CardStack cS = { false, a, {false, false, false, false}, (cRank)b };
	return cS;
}

bool compareCardStacks(const CardStack & a, const CardStack & b) {
	if ((!a.canPut) && b.canPut)
		return false;
	else if (a.canPut && (!b.canPut))
		return true;

	if (a.num < b.num)
		return false;
	else if (a.num > b.num)
		return true;

	return ((int)a.type < (int)b.type);
}
