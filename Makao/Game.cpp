#include "Game.h"

#define DEBUG

#ifdef DEBUG
#include "Helpers/CardToString.h"

void print_cards(int player_number, std::vector<Card*> cards) {
	printf("\t%d:\n", player_number);
	for (auto& card : cards)
	{
		printf("\t\t%s\n", cardToString(card).c_str());
	}
}
#endif

Game::Game() {
	stack = new Stack();
	deck = new Deck();
	deck->Shuffle();
}

Game::Game(int playerCount) : results(playerCount, 0), finished(playerCount, false), otherPlayersCards(playerCount - 1, 0), otherPlayersStops(playerCount - 1, 0) {
	stack = new Stack();
	deck = new Deck();
	deck->Shuffle();
	this->players.insert(std::end(this->players), std::begin(players), std::end(players));
}

Game::Game(std::vector<Player*> players) : results(players.size(), 0), finished(players.size(), false), otherPlayersCards(players.size() - 1, 0), otherPlayersStops(players.size() - 1, 0) {
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
		std::vector<Card*> starting_cards = deck->DrawCards(startingCardNumber);
		players[i]->SetCards(starting_cards);
	}
}

std::vector<int> Game::Play() {
	for (int i = 0; i < players.size() - 1; i++)
	{
		otherPlayersCards[i] = players[i % players.size()]->getCardNumber();
		results[i] = 0;
		finished[i] = false;
	}
	results[players.size() - 1] = 0;
	finished[players.size() - 1] = false;
	stack->makeAbsoluteStoppedPlayers(players.size());
	int currentPrize = 3, playerCount = players.size(), maximumTurnNumber = 1000, valetResetSpot = -1;
	Card* drawnCard;
	std::vector<Card*> drawnCards, lastHand, moveResult;

	while (playerCount > 1 && maximumTurnNumber)
	{
#ifdef DEBUG
		printf("===================\n");
		printf("GAMESTATE:\n");
		int player_card_sum = 0;
		for (int i = 0; i < players.size(); i++)
		{
			print_cards(i, players[i]->Hand);
			player_card_sum += players[i]->getCardNumber();
		}
		printf("Top card: %s\n", cardToString(stack->BottomCards.back()).c_str());
		printf("Deck size: %d\n", deck->getCardNumber());
		printf("Stack size: %d\n", (int)stack->BottomCards.size());
		int card_sum = (int)stack->BottomCards.size() + deck->getCardNumber() + player_card_sum;
		printf("Total cards: %d\n", card_sum);
#endif
		--maximumTurnNumber;	//Solution for infinite games
		for (int i = 0; i < players.size(); i++)
		{
			if (finished[i])	//If player already finished
			{
				if (i == valetResetSpot)
				{
					stack->resetDesiredRank();
					valetResetSpot = -1;
				}
				continue;
			}
			else if (stack->getAbsoluteStoppedPlayers(i) != 0)	//if player is stopped
			{

				if (i == valetResetSpot)
				{
					stack->resetDesiredRank();
					valetResetSpot = -1;
				}
				stack->decreaseAbsoluteStoppedPlayers(i);

				otherPlayersCards.erase(otherPlayersCards.begin());		//updating which card numbers does players see
				otherPlayersCards.push_back(players[i]->getCardNumber());

				otherPlayersStops.erase(otherPlayersStops.begin());
				otherPlayersStops.push_back(stack->getAbsoluteStoppedPlayers(i));

				continue;
			}

			std::vector<Card*> validation_cards = players[i]->Hand;
			moveResult = players[i]->MakeAMove(stack, otherPlayersCards, otherPlayersStops);	//Make a move
			std::vector<Card*> validation_after = players[i]->Hand;
			validation_after.insert(std::end(validation_after), std::begin(moveResult), std::end(moveResult));
			std::sort(validation_cards.begin(), validation_cards.end());
			std::sort(validation_after.begin(), validation_after.end());
			if (validation_cards != validation_after)
			{
				results[i] = 0;
				finished[i] = true;
				playerCount--;

				if (i == valetResetSpot)
				{
					stack->resetDesiredRank();
					valetResetSpot = -1;
				}

				deck->PutCards(validation_cards);
				players[i]->Hand.clear();

#ifdef DEBUG
				printf("%d: !!!!!!!ILLEGAL!!!!!!!\n", i);
#endif

				continue;
			}

#ifdef DEBUG
			if (stack->getDesiredSuit() != cSuit::None)
				printf(" Desired suit: %s\n", cSuitToString(stack->getDesiredSuit()).c_str());
			if (stack->getDesiredCard() != cRank::Joker)
				printf(" Desired card: %s\n", cRankToString(stack->getDesiredCard()).c_str());
			printf("  Move made:\n");
			print_cards(i, moveResult);
#endif

			if (i == valetResetSpot)
			{
				stack->resetDesiredRank();
				valetResetSpot = -1;
			}

			if (moveResult.size() != 0 && !stack->TryCards(moveResult))	//Move was invalid
			{
				players[i]->DrawCard(moveResult);
				moveResult.clear();
#ifdef DEBUG
				printf("!!INVALID MOVE!!\n");
#endif
			}
			else if (moveResult.size() != 0)
			{
				if (stack->getDesiredSuit() != cSuit::None)
				{
					stack->resetDesiredSuit();
				}

				if (moveResult[0]->Rank == cRank::Valet) // Valet was played, remember for a reset
					valetResetSpot = i;
			}

			if (moveResult.size() == 0)	//no move
			{
				if (stack->getDrawStack() != 0)	//draw drawStack
				{
#ifdef DEBUG
					printf("&Drawing multiple: %d\n", stack->getDrawStack());
#endif
					drawnCards = deck->DrawCards(stack->getDrawStack());
					if (drawnCards.size() != 0)
						players[i]->DrawCard(drawnCards);
					stack->clearDrawStack();
				}
				else if (stack->getStopStack() != 0)	//stop for stopStack
				{
#ifdef DEBUG
					printf("&Stopping for: %d\n", stack->getStopStack());
#endif
					stack->setAbsoluteStoppedPlayer(i);
					stack->clearStopStack();
				}
				else	//draw a card
				{
#ifdef DEBUG
					printf("&No move, draw 1\n");
#endif
					drawnCard = deck->DrawCards();
					if (drawnCard != nullptr)
						players[i]->DrawCard(drawnCard);
				}
			}
			else if (players[i]->getCardNumber() == 0)	//player won
			{
#ifdef DEBUG
				printf("PLAYER WON: %d\n", i);
#endif
				results[i] = currentPrize--;
				finished[i] = true;
				playerCount--;

				if (currentPrize == 0)	//last man standing
					break;
			}
			else if (stack->getTopCard().Rank == cRank::King && stack->getTopCard().Suit == cSuit::Spades)	//If King of Spades, the drawStack goes backwards one player
			{
				i = (i > 1) ? i - 2 : playerCount + (i - 2);
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
		}
	}	

	lastHand = stack->Clear();	//get cards from stack
	deck->PutCards(lastHand);

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
