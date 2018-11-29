#include "Deck.h"
#include "Stack.h"
#include "Cards.h"
#include "Game.h"
#include "Player.h"
#include "AgaBot.h"
#include "Supa_Player.h"
#include "BasicBDiamondDBot.h"

typedef struct {
	Player* player;
	std::string name;
	int points;
}PlayerInfo;

void setPlayerInfoPointer(PlayerInfo* PI, Player* player, std::string name) {
	PI->player = player;
	PI->name = name;
	PI->points = 0;
}

int main()
{
	std::srand(unsigned(std::time(0)));

	Game* game = new Game();

	std::vector<PlayerInfo> players;
	for(int i=0; i<4; i++)
		players.push_back(PlayerInfo());

	setPlayerInfoPointer(&(players[0]), new Player(), "Player");
	setPlayerInfoPointer(&(players[1]), new AgaBot(), "AgaBot");
	setPlayerInfoPointer(&(players[2]), new Supa_Player(), "Supa_Player");
	setPlayerInfoPointer(&(players[3]), new BasicBDiamondDBot(), "BasicBDiamondDBot");

	std::vector<Player*> currentPlayers;

	std::vector<int> results;

	int N = 5;
	while (N--)
	{
		random_shuffle(players.begin(), players.end());	//Take 4 random players
		for (int i = 0; i < 4; i++)
			currentPlayers.push_back(players[i].player);

		game->AddPlayer(currentPlayers);
		game->SetUp();

		for (int i = 0; i < 4; i++)
			printf("%s\n", players[i].name.c_str());

		results = game->Play();

		for (int i = 0; i < 4; i++)
			players[i].points += results[i];
		game->Clear();
		currentPlayers.clear();

		printf("\t%d\n", N);
	}

	int maxNameLength=0;
	for (int i = 0; i < players.size(); i++)
		if(maxNameLength < players[i].name.length()) 
			maxNameLength = players[i].name.length();
	for(int i=0; i<players.size(); i++)
		printf("%-*s\t%d\n", maxNameLength, players[i].name.c_str(), players[i].points);

    return 0;
}

