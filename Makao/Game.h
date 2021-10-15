#pragma once
#include <vector>
#include <time.h>
#include "Stack.h"
#include "Deck.h"
#include "Players/Player.h"

class Game {
	private:
		const int startingCardNumber = 5;
		std::vector<int> results, otherPlayersCards, otherPlayersStops;
		std::vector<bool> finished;
		std::vector<Player*> players;
		Stack* stack;
		Deck* deck;
	public:
		Game();
		Game(int playerCount);
		Game(std::vector<Player*> players);
		void AddPlayer(Player* player);
		void AddPlayer(std::vector<Player*> players);
		void SetUp();
		std::vector<int> Play();
		void Clear();
		~Game();
};