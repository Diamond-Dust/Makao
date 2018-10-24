#pragma once
#include "Card.h"
#include <vector>

bool CanBePut(Card first, Card next, std::vector<int> drawStack, cRank desiredCard, int stopStack);