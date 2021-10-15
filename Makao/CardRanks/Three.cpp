#include "Three.h"

Three::Three() : Card(cRank::Three, cSuit::None) {

}

Three::Three(cSuit suit) : Card(cRank::Three, suit) {

}

void Three::Function(int& drawStack, cSuit& desiredSuit, cRank & desiredCard, int & stopStack) {
	drawStack+=3;
}
