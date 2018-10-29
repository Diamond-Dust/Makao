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

	
	while (true)
	{
		game->AddPlayer(players);
		game->SetUp();
		results = game->Play();
		game->Clear();
	}
	

    return 0;
}

