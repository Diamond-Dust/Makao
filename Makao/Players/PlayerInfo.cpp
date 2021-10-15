#include "PlayerInfo.h"

void setPlayerInfoPointer(PlayerInfo* PI, Player* player, std::string name) {
	PI->player = player;
	PI->name = name;
	PI->points = 0;
}
