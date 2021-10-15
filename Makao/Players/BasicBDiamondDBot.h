//Bot by Diamond Dust
#pragma once
#include "Player.h"

typedef struct {
	bool canPut;
	int num;
	bool col[(int)cSuit::COUNT];
	cRank type;
} CardStack;

CardStack makeCardStack(int a, cRank b);
CardStack makeCardStack(int a, int b);
bool compareCardStacks(const CardStack &a, const CardStack &b);

class BasicBDiamondDBot : public Player {
	private:
		std::vector<CardStack> StackHand();
		std::vector<CardStack> PutCheckCardStack(std::vector<CardStack> cStack, const Stack* stack);
		std::vector<CardStack> sortCardStack(std::vector<CardStack> cStack);
		std::pair<bool, cRank> ValetChain;
		bool CheckValetChain(const Stack* stack, std::vector<Card*> & toThrow, std::vector<CardStack> & cStack);
		bool CheckKingCombo(const Stack* stack, std::vector<Card*> & toThrow, std::vector<CardStack> & cStack);
		bool CheckTwoThreePlay(int nextPlayerCards, const Stack* stack, std::vector<Card*> & toThrow, CardStack* two, CardStack* three);
		bool CheckDrawCards(int nextPlayerCards, const Stack* stack, std::vector<Card*> & toThrow, std::vector<CardStack> & cStack);
	public:
		BasicBDiamondDBot();
		std::vector<Card*> MakeAMove(const Stack* stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops);
};