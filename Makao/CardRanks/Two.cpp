#include "Two.h"

Two::Two() : Card(cRank::Two, cSuit::None) {

}

Two::Two(cSuit suit) : Card(cRank::Two, suit) {

}

void Two::Function(int& drawStack, cSuit& desiredSuit, cRank & desiredCard, int & stopStack) {
	drawStack+=2;
}
