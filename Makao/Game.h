#pragma once
#include <vector>
#include "Stack.h"
#include "Deck.h"
#include "Player.h"

class Game {
	private:
		const int startingCardNumber = 5;
		std::vector<Player*> players;
		Stack* stack;
		Deck* deck;
	public:
		Game();
		Game(std::vector<Player*> players);
		void AddPlayer(Player* player);
		void AddPlayer(std::vector<Player*> players);
		void SetUp();
		std::vector<int> Play();
		void Clear();
		~Game();
};