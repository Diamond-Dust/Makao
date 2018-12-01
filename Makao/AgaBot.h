//Bot by AH, written by Diamond Dust
#pragma once
#include "Player.h"

class AgaBot : public Player {
private:

	std::vector<cSuit> suits;
	std::vector<int> sums;
	std::pair<bool, cRank> ValetChain;
	std::pair<bool, cSuit> AceChain;
	bool End(std::vector<Card*>& pCards, std::vector<Card*> & toThrow);
	std::vector<cSuit> SumBySuit();
	int SumFours();
	int SumDraws();
	int SumRanks();
public:
	AgaBot();
	std::vector<Card*> MakeAMove(const Stack* stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops);
	~AgaBot();
};

