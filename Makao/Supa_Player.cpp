#include "Supa_Player.h"

Supa_Player::Supa_Player() {
}

std::vector<Card*> Supa_Player::MakeAMove(Stack * stack, std::vector<int> otherPlayersCards, std::vector<int> otherPlayersStops){
	std::vector<Card*> thrownCards;
	Card top_card = stack->getTopCard();
	// TODO if you have a jack use it you dummy
	// TODO if you have ace use it ya big doofus
	// TODO look at how much other players card have ya big dingus.

	// boi you about to get slapped
	if (top_card.Functional) {
		// look for functionals to play
		for (int i = 0; i < Hand.size(); i++) {
			if (Hand[i]->Functional
				&& CanBePut(stack->getTopCard(), *Hand[i], stack->getDrawStack(),
					stack->getDesiredSuit(), stack->getDesiredCard(), stack->getStopStack())) {
				// found functional to play
				// TODO decide whether to play multiple functionals 
				thrownCards.push_back(Hand[i]);
				Hand.erase(Hand.begin() + i);
				break;
			}
		}
		if (!thrownCards.empty())
			return thrownCards;
		else
			return Player::MakeAMove(stack, otherPlayersCards, otherPlayersStops);
	}
	// okay no pressure
	else {
		// look for non functionals to play
		for (int i = 0; i < Hand.size(); i++) {
			if (!(Hand[i]->Functional)
				&& CanBePut(stack->getTopCard(), *Hand[i], stack->getDrawStack(), 
					stack->getDesiredSuit(), stack->getDesiredCard(), stack->getStopStack())) {
				thrownCards.push_back(Hand[i]);
				Hand.erase(Hand.begin() + i);
				// found non functional to play, looking for it's brothers and sisters
				std::vector<Card*>::iterator iter;
				for (iter = Hand.begin(); iter != Hand.end();) {
					if ((*iter)->Rank == thrownCards[0]->Rank) {
						// found a brotha or a sista
						thrownCards.push_back((*iter));
						iter = Hand.erase(iter);
					}
					else
						iter++;
				}
				break;
			}
		}
		if (!thrownCards.empty())
			return thrownCards;
		else
			return Player::MakeAMove(stack, otherPlayersCards, otherPlayersStops);
	}
}

Supa_Player::~Supa_Player() {
}