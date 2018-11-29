//Fischer-Yates shuffle with set iterations by Michael Burr
#pragma once
#include <vector>
#include <algorithm>
#include <cstdlib>

template<class BidiIter >
BidiIter random_unique(BidiIter begin, BidiIter end, size_t num_random);