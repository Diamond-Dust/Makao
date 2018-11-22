#pragma once
#include "Player.h"

class Supa_Player : public Player {
public:
	Supa_Player();
	virtual std::vector<Card*> MakeAMove(Stack* stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops);
	~Supa_Player();
};

