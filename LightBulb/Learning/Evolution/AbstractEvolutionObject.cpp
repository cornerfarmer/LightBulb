// Includes
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
// Library includes
#include <stdlib.h>

void AbstractEvolutionObject::randomizeMutationStrength()
{
	// Go through all mutation strength values
	for (auto mutationStrengthValue = mutationStrength.begin(); mutationStrengthValue != mutationStrength.end(); mutationStrengthValue++)
	{
		// Set it to a random value
		*mutationStrengthValue = (float)rand() / RAND_MAX * 0.1;
	}
}

std::vector<double>* AbstractEvolutionObject::getMutationStrength()
{
	return &mutationStrength;
}

void AbstractEvolutionObject::setMutationStrength(std::vector<double>* newMutationStrength)
{
	mutationStrength = *newMutationStrength;
}

void AbstractEvolutionObject::resizeMutationStrength(int newSize)
{
	mutationStrength.resize(newSize);
}
