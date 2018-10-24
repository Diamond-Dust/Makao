#include "Deck.h"
#include "Stack.h"
#include "Cards.h"

int main()
{
	Stack* stack = new Stack(new Card(cRank::Queen, cSuit::Hearts));
	stack->TryCards(new Card(cRank::King, cSuit::Hearts));

    return 0;
}

