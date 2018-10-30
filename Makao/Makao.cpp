#include "Deck.h"
#include "Stack.h"
#include "Cards.h"
#include "Game.h"
#include "Player.h"

int main()
{
	//Stack* stack = new Stack(new Card(cRank::Queen, cSuit::Hearts));
	//stack->TryCards(new King(cSuit::Hearts));
	
	//Deck* deck = new Deck;
	//deck->Shuffle();
	//std::vector<Card*> cards = deck->DrawCards(5);

	Game* game = new Game();
	std::vector<Player*> players;
	for (int i = 0; i < 4; i++)
		players.push_back(new Player());
	std::vector<int> results;
	std::vector<int> fullResults;
	for (int i = 0; i < 4; i++)
		fullResults.push_back(0);

	int N = 10000;
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
	for (int i = 0; i < 4; i++)
		printf("%d\n", fullResults[i]);

    return 0;
}

