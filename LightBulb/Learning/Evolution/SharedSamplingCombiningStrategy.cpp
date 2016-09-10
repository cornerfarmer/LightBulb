// Includes
#include "Learning/Evolution/SharedSamplingCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

namespace LightBulb
{
	void SharedSamplingCombiningStrategy::combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects)
	{
		if (!otherCombiningStrategy)
			throw std::invalid_argument("SharedSamplingCombiningStrategy only works with two worlds.");

		std::vector<AbstractEvolutionObject*> sample;
		std::map<AbstractEvolutionObject*, std::map<int, int>> beat;
		std::map<AbstractEvolutionObject*, double> sampleFitness;
		auto prevResults = otherCombiningStrategy->getPrevResults();
		while (sample.size() < amountOfCompetitionsPerObject)
		{
			AbstractEvolutionObject* bestObject = NULL;
			for (auto secondPlayer = secondObjects->begin(); secondPlayer != secondObjects->end(); secondPlayer++)
			{
				if (sampleFitness[*secondPlayer] != -1)
				{
					sampleFitness[*secondPlayer] = 0;
					for (auto resultsPerSecondPlayer = (*prevResults)[*secondPlayer].begin(); resultsPerSecondPlayer != (*prevResults)[*secondPlayer].end(); resultsPerSecondPlayer++)
					{
						for (auto result = resultsPerSecondPlayer->second.begin(); result != resultsPerSecondPlayer->second.end(); result++)
						{
							if (result->second)
								sampleFitness[*secondPlayer] += 1.0 / (1 + beat[resultsPerSecondPlayer->first][result->first]);
						}
					}
					if (bestObject == NULL || sampleFitness[bestObject] < sampleFitness[*secondPlayer])
						bestObject = *secondPlayer;
				}
			}
			if (!bestObject)
				break;

			sample.push_back(bestObject);
			sampleFitness[bestObject] = -1;
			for (auto resultsPerSecondPlayer = (*prevResults)[bestObject].begin(); resultsPerSecondPlayer != (*prevResults)[bestObject].end(); resultsPerSecondPlayer++)
			{
				for (auto result = resultsPerSecondPlayer->second.begin(); result != resultsPerSecondPlayer->second.end(); result++)
				{
					if (result->second)
						beat[resultsPerSecondPlayer->first][result->first]++;
				}
			}
		}

		for (auto firstPlayer = firstObjects->begin(); firstPlayer != firstObjects->end(); firstPlayer++)
		{
			for (auto secondPlayer = sample.begin(); secondPlayer != sample.end(); secondPlayer++)
			{
				if (*firstPlayer != *secondPlayer)
				{
					for (int r = 0; r < simulationWorld->getRoundCount(); r++)
					{
						int result = simulationWorld->compareObjects(*firstPlayer, *secondPlayer, r);
						if (result != 0)
							setResult(*firstPlayer, *secondPlayer, r, result > 0);
					}
				}
			}
		}
	}

	void SharedSamplingCombiningStrategy::setSecondWorld(AbstractCoevolutionWorld* newSecondWorld)
	{
		AbstractCombiningStrategy::setSecondWorld(newSecondWorld);
		otherCombiningStrategy = secondWorld->getCombiningStrategy();
	}

	SharedSamplingCombiningStrategy::SharedSamplingCombiningStrategy(int amountOfCompetitionsPerObject_, AbstractCoevolutionWorld* secondWorld_)
		:AbstractCombiningStrategy(secondWorld_)
	{
		if (secondWorld)
			otherCombiningStrategy = secondWorld->getCombiningStrategy();
		amountOfCompetitionsPerObject = amountOfCompetitionsPerObject_;
	}


	int SharedSamplingCombiningStrategy::getTotalMatches(AbstractCoevolutionWorld* simulationWorld)
	{
		return amountOfCompetitionsPerObject * simulationWorld->getPopulationSize() * simulationWorld->getRoundCount();
	}

}