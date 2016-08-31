// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

void AbstractRandomGeneratorUser::setRandomGenerator(AbstractRandomGenerator* randomGenerator_)
{
	randomGenerator = randomGenerator_;
}

AbstractRandomGenerator* AbstractRandomGeneratorUser::getRandomGenerator()
{
	return randomGenerator;
}
