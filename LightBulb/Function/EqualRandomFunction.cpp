// Includes
#include "Function/EqualRandomFunction.hpp"
// Library includes
#include <random>
#include <algorithm>

int EqualRandomFunction::execute(int elementCount)
{
	return std::min(elementCount - 1, (int)((float)rand() / RAND_MAX * elementCount));
}
