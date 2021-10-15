#pragma once

#include<string>
#include "../CardRanks/Card.h"
#include "../Cards.h"

std::string cSuitToString(cSuit suit);
std::string cRankToString(cRank rank);
std::string cardToString(Card* card);