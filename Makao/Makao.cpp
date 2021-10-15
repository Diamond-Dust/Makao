#include "Deck.h"
#include "Stack.h"
#include "Cards.h"
#include "Game.h"
#include "Helpers/FileHandler.h"
#include "Helpers/WindowsBenchmarking.h"
#include "Players/PlayerInfo.h"
#include "Players/Player.h"
#include "Players/AgaBot.h"
#include "Players/Supa_Player.h"
#include "Players/BasicBDiamondDBot.h"

#define DEBUG

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

	int N = 100;
	for(int n = 0; n < N; n++)
	{
		random_shuffle(players.begin(), players.end());	//Take 4 random players
		for (int i = 0; i < 4; i++)
			currentPlayers.push_back(players[i].player);

#ifdef DEBUG
		printf("Players:\n");
		for (int i = 0; i < 4; i++)
			printf("\t%s\n", players[i].name.c_str());
#endif

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

		printf("\tGame number:\t%d\n", n);
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

