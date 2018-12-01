#include "Deck.h"
#include "Stack.h"
#include "Cards.h"
#include "Game.h"
#include "FileHandler.h"
#include "WindowsBenchmarking.h"
#include "PlayerInfo.h"
#include "Player.h"
#include "AgaBot.h"
#include "Supa_Player.h"
#include "BasicBDiamondDBot.h"

int main()
{
	std::srand(unsigned(std::time(0)));
	WinBench Q;

	Game* game = new Game(4);

	std::vector<PlayerInfo> players;
	for(int i=0; i<4; i++)
		players.push_back(PlayerInfo());

	setPlayerInfoPointer(&(players[0]), new Player(), "Player");
	setPlayerInfoPointer(&(players[1]), new AgaBot(), "AgaBot");
	setPlayerInfoPointer(&(players[2]), new Supa_Player(), "Supa_Player");
	setPlayerInfoPointer(&(players[3]), new BasicBDiamondDBot(), "BasicBDiamondDBot");

	std::vector<Player*> currentPlayers;

	std::vector<int> results;

	double time = 0;

	int N = 10;
	for(int n = 0; n < N; n++)
	{
		random_shuffle(players.begin(), players.end());	//Take 4 random players
		for (int i = 0; i < 4; i++)
			currentPlayers.push_back(players[i].player);

		game->AddPlayer(currentPlayers);
		game->SetUp();

		Q.StartCounter();

		results = game->Play();
		
		printf("Total:\t%lf\n", Q.GetCounter(1000));
		time += Q.GetCounter(1000);

		for (int i = 0; i < 4; i++)
			players[i].points += results[i];
		game->Clear();
		currentPlayers.clear();

		printf("\tGra numer:\t%d\n", n);
	}

	FileHandler FH("Simulation Results.txt", "a");

	printf("Average time per game:\t%lf\n", time/(double)N);

	int maxNameLength=0;
	for (int i = 0; i < players.size(); i++)
		if(maxNameLength < players[i].name.length()) 
			maxNameLength = players[i].name.length();

	FH.PrintSimEnd(N, time / (double)N, maxNameLength, players);

	for (int i = 0; i < players.size(); i++)
		printf("%-*s\t%d\n", maxNameLength, players[i].name.c_str(), players[i].points);

    return 0;
}

