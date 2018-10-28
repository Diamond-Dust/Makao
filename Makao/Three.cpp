#include "Three.h"

Three::Three() : Card(cRank::Three, cSuit::None) {

}

Three::Three(cSuit suit) : Card(cRank::Three, suit) {

}

void Three::Function(std::vector<int>& drawStack, cSuit& desiredSuit, cRank & desiredCard, int & stopStack) {
	drawStack.push_back(3);
}
