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
	std::vector<int> results, otherPlayersCards, otherPlayersStops;
	std::vector<bool> finished;
	for (int i = 0; i < players.size(); i++)
	{
		results.push_back(0);
		finished.push_back(false);
		if (i > 0)
		{
			otherPlayersCards.push_back(players[i % players.size()]->getCardNumber());
			otherPlayersStops.push_back(0);
		}
	}
	stack->makeAbsoluteStoppedPlayers(players.size());
	int currentPrize = 3, playerCount = players.size(), maximumTurnNumber = 10000;
	Card* drawnCard;
	std::vector<Card*> drawnCards, lastHand, moveResult;

	while (playerCount > 1 && maximumTurnNumber)
	{
		--maximumTurnNumber;	//Solution for infinite games
		for (int i = 0; i < players.size(); i++)
		{

			if (finished[i])	//If player already finished
				continue;
			else if (stack->getAbsoluteStoppedPlayers()[i] != 0)	//if player is stopped
			{
				stack->decreaseAbsoluteStoppedPlayers(i);

				otherPlayersCards.erase(otherPlayersCards.begin());		//updating which card numbers does players see
				otherPlayersCards.push_back(players[i]->getCardNumber());

				otherPlayersStops.erase(otherPlayersStops.begin());
				otherPlayersStops.push_back(stack->getAbsoluteStoppedPlayers(i));

				continue;
			}

			moveResult = players[i]->MakeAMove(stack, otherPlayersCards, otherPlayersStops);	//Make a move

			if (moveResult.size() != 0 && !stack->TryCards(moveResult))	//Move was invalid
			{
				players[i]->DrawCard(moveResult);
				moveResult.clear();
			}
			else if (moveResult.size() == 0)	//no move
			{
				if (stack->getDrawStack() != 0)	//draw drawStack
				{
					drawnCards = deck->DrawCards(stack->getDrawStack());
					if (drawnCards.size() != 0)
						players[i]->DrawCard(drawnCards);
					stack->clearDrawStack();
				}
				else if (stack->getStopStack() != 0)	//stop for stopStack
				{
					stack->setAbsoluteStoppedPlayer(i);
					stack->clearStopStack();
				}
				else	//draw a card
				{
					drawnCard = deck->DrawCards();
					if (drawnCard != nullptr)
						players[i]->DrawCard(drawnCard);
				}
			}
			else if (players[i]->getCardNumber() == 0)	//player won
			{
				results[i] = currentPrize--;
				finished[i] = true;
				playerCount--;

				if (currentPrize == 0)	//last man standing
					break;
			}
			else if (stack->getTopCard().Rank == cRank::King && stack->getTopCard().Suit == cSuit::Spades)	//If King of Spades, the drawStack goes backwards one player
			{
				i = (i > 1) ? i-2 : playerCount + (i-2);
			}

			if (deck->getCardNumber() <= stack->getDrawStack())	//not enough cards in deck
			{
				deck->PutCards(stack->RemoveBottom());
				deck->ResetValetsAndAces();
			}

			otherPlayersCards.erase(otherPlayersCards.begin());		//updating which card numbers does players see
			otherPlayersCards.push_back(players[i]->getCardNumber());

			otherPlayersStops.erase(otherPlayersStops.begin());
			otherPlayersStops.push_back(stack->getAbsoluteStoppedPlayers(i));

		}
	}

	for (int i = 0; i < players.size(); i++)
	{
		if (finished[i] == false)
		{
			lastHand = players[i]->Hand;	//get cards from last player to deck
			players[i]->Hand.clear();
			deck->PutCards(lastHand);

			lastHand = stack->Clear();	//get cards from stack
			deck->PutCards(lastHand);

			break;
		}
	}	
	deck->ResetValetsAndAces();

	return results;
}

void Game::Clear() {
	deck->Shuffle();
	deck->ResetValetsAndAces();
	players.clear();
}

Game::~Game() {
	delete stack;
	delete deck;
}
