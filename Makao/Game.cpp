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
	int currentPrize = 3, moveResult;
	Card* drawnCard;
	std::vector<Card*> drawnCards;

	while(players.size() != 1)
		for (int i = 0; i < players.size(); i++)
		{
			moveResult = players[i]->MakeAMove(stack);
			if (moveResult == -1)	//no move
			{
				if (stack->getDrawStack() != 0)	//draw drawStack
				{
					drawnCards = deck->DrawCards(stack->getDrawStack());
					if (drawnCards.size() != 0)
						players[i]->DrawCard(drawnCards);
					stack->clearDrawStack();
				}
				else if (stack->getStopStack() != 0)
				{
					stack->clearStopStack();	//! TODO: IMPLEMENT STOPSTACK
				}

				drawnCard = deck->DrawCards();	//draw a card
				if (drawnCard != nullptr)
					players[i]->DrawCard(drawnCard);
			}
			else if (moveResult == 0)	//player won
			{
				results[i] = currentPrize--;
				players.erase(players.begin() + i);
			}

			if (deck->getCardNumber() <= stack->getDrawStack())	//not enough cards in deck
				deck->PutCards(stack->RemoveBottom());
			
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
