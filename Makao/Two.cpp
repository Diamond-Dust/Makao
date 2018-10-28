#include "Two.h"

Two::Two() : Card(cRank::Two, cSuit::None) {

}

Two::Two(cSuit suit) : Card(cRank::Two, suit) {

}

void Two::Function(std::vector<int>& drawStack, cSuit& desiredSuit, cRank & desiredCard, int & stopStack) {
	drawStack.push_back(2);
}
