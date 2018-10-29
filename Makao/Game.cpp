#include "Game.h"

Game::Game() {
	stack = new Stack();
	deck = new Deck();
	deck->Shuffle();
}

Game::Game(std::vector<Player*> players) {
	stack = new Stack();
	deck = new Deck();
	deck->Shuffle();
	this->players.insert(std::end(this->players), std::begin(players), std::end(players));

}

void Game::AddPlayer(Player * player) {
	players.push_back(player);
}

void Game::AddPlayer(std::vector<Player*> players) {
	this->players.insert(std::end(this->players), std::begin(players), std::end(players));
}

void Game::SetUp() {
	Card* startingCard = deck->DrawCards();
	while(startingCard->Functional)
	{
		deck->PutCards(startingCard);
		startingCard = deck->DrawCards();
	}

	stack->TryCards(startingCard);

	for (int i = 0; i < players.size(); i++)
	{
		players[i]->SetCards(deck->DrawCards(startingCardNumber));
	}
}

std::vector<int> Game::Play() {
	std::vector<int> results;
	results.reserve(players.size());
	int currentPrize = 3;

	while(players.size() != 1)
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i]->MakeAMove(stack, deck) == 0)
			{
				results[i] = currentPrize--;
				players.erase(players.begin() + i);
			}
			
		}

	return results;
}

void Game::Clear() {
	delete stack;
	delete deck;
	stack = new Stack();
	deck = new Deck();
	deck->Shuffle();
	players.clear();
}

Game::~Game() {
	delete stack;
	delete deck;
}
