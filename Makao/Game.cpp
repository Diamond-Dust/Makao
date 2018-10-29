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
	std::vector<bool> finished;
	for (int i = 0; i < players.size(); i++)
	{
		results.push_back(0);
		finished.push_back(false);
	}
	int currentPrize = 3, moveResult, playerCount = players.size();
	Card* drawnCard;
	std::vector<Card*> drawnCards;
	int counter = 0;

	while (playerCount > 1)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (finished[i])	//If player already finished
				continue;

			moveResult = players[i]->MakeAMove(stack);	//Make a move

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
				else	//draw a card
				{
					drawnCard = deck->DrawCards();
					if (drawnCard != nullptr)
						players[i]->DrawCard(drawnCard);
				}
			}
			else if (moveResult == 0)	//player won
			{
				results[i] = currentPrize--;
				finished[i] = true;
				playerCount--;
				//players.erase(players.begin() + i);
			}

			if (deck->getCardNumber() <= stack->getDrawStack())	//not enough cards in deck
				deck->PutCards(stack->RemoveBottom());

			if (players.size() > i)
				printf("%d:\t%d\t%d\n", counter++, i, players[i]->getCardNumber());
			//counter++;
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
