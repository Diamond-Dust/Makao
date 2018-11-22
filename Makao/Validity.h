#pragma once
#include "Card.h"
#include "Stack.h"
#include <vector>

bool CanBePut(Card first, Card next, int drawStack, cSuit desiredSuit, cRank desiredCard, int stopStack);
bool CanBePut(const Stack* stack, Card next);
bool IsFunctional(cRank rank);
bool IsDraw(Card card);