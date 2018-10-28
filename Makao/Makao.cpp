#include "Deck.h"
#include "Stack.h"
#include "Cards.h"

int main()
{
	Stack* stack = new Stack(new Card(cRank::Queen, cSuit::Hearts));
	stack->TryCards(new Card(cRank::King, cSuit::Hearts));
	Deck* deck = new Deck;
	deck->Shuffle();
	std::vector<Card*> cards = deck->DrawCards(5);

    return 0;
}

