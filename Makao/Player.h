#pragma once
#include <vector>
#include "Validity.h"
#include "Card.h"
#include "Stack.h"
#include "Deck.h"


class Player {
	friend class Game;
private:
	std::vector<Card*> Hand;
	void SetCards(std::vector<Card*> cards);
	void DrawCard(Card* card);
	void DrawCard(std::vector<Card*> cards);
public:
	Player();
	virtual std::vector<Card*> MakeAMove(Stack* stack, std::vector<int> otherPlayersCards);
	int getCardNumber();
	~Player();
};