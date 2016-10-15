// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

namespace LightBulb
{
	AbstractRandomGeneratorUser::AbstractRandomGeneratorUser()
	{
		randomGenerator = NULL;
	}

	void AbstractRandomGeneratorUser::setRandomGenerator(AbstractRandomGenerator* randomGenerator_)
	{
		randomGenerator = randomGenerator_;
	}

	AbstractRandomGenerator* AbstractRandomGeneratorUser::getRandomGenerator()
	{
		return randomGenerator;
	}
}