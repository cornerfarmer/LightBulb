// Includes
#include "Learning/Evolution/RoundRobinCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

RoundRobinCombiningStrategy::RoundRobinCombiningStrategy(AbstractCoevolutionFitnessFunction* fitnessFunction_)
	:AbstractCombiningStrategy(fitnessFunction_)
{
}

void RoundRobinCombiningStrategy::combine(AbstractCoevolutionWorld* world)
{
	for (auto firstPlayer = world->getEvolutionObjects()->begin(); firstPlayer != world->getEvolutionObjects()->end(); firstPlayer++)
	{
		for (auto secondPlayer = world->getEvolutionObjects()->begin(); secondPlayer != world->getEvolutionObjects()->end(); secondPlayer++)
		{
			if (*firstPlayer != *secondPlayer)
			{
				int result = world->compareObjects(*firstPlayer, *secondPlayer);
				if (result != 0)
					setResult(*firstPlayer, *secondPlayer, result > 0);
			}
		}
	}
}

