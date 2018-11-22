#pragma once
#include <vector>
#include "Validity.h"
#include "Card.h"
#include "Stack.h"
#include "Deck.h"


class Player {
	friend class Game;
private:
	void SetCards(std::vector<Card*> cards);
	void DrawCard(Card* card);
	void DrawCard(std::vector<Card*> cards);
protected:
	std::vector<Card*> Hand;
public:
	Player();
	virtual std::vector<Card*> MakeAMove(const Stack* stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops);
	int getCardNumber();
	~Player();
};
