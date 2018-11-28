#include "Deck.h"
#include "Stack.h"
#include "Cards.h"
#include "Game.h"
#include "Player.h"
#include "Supa_Player.h"
#include "BasicBDiamondDBot.h"

int main()
{
	Game* game = new Game();
	std::vector<Player*> players;
	for (int i = 0; i < 2; i++)
		players.push_back(new Player());
	players.push_back(new Supa_Player());
	players.push_back(new BasicBDiamondDBot());
	std::vector<int> results;
	std::vector<int> fullResults;
	for (int i = 0; i < 4; i++)
		fullResults.push_back(0);

	int N = 10;
	while (N--)
	{
		game->AddPlayer(players);
		game->SetUp();
		results = game->Play();
		for (int i = 0; i < 4; i++)
			fullResults[i] += results[i];
		game->Clear();
		printf("\t%d\n", N);
	}
	for (int i = 0; i < 2; i++)
		printf("Player%d:\t\t%d\n", i, fullResults[i]);
	printf("Supa_Player:\t\t%d\n", fullResults[2]);
	printf("BasicBDiamondDBot:\t%d\n", fullResults[3]);

    return 0;
}

