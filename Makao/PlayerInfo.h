#pragma once
#include "Player.h"
#include <string>

typedef struct {
	Player* player;
	std::string name;
	int points;
}PlayerInfo;

void setPlayerInfoPointer(PlayerInfo* PI, Player* player, std::string name);