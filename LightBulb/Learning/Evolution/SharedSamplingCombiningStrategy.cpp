// Includes
#include "Learning/Evolution/SharedSamplingCombiningStrategy.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
//Library includes
#include <algorithm>
#include <iostream>

void SharedSamplingCombiningStrategy::combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects)
{
	std::vector<AbstractEvolutionObject*> sample;
	std::map<AbstractEvolutionObject*, int> beat;
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
				for (auto result = (*prevResults)[*secondPlayer].begin(); result != (*prevResults)[*secondPlayer].end(); result++)
				{
					if (result->second)
						sampleFitness[*secondPlayer] += 1 / (1 + beat[result->first]);
				}
				if (bestObject == NULL || sampleFitness[bestObject] < sampleFitness[*secondPlayer])
					bestObject = *secondPlayer;
			}
		}
		if (!bestObject)
			break;

		sample.push_back(bestObject);
		sampleFitness[bestObject] = -1;
		for (auto result = (*prevResults)[bestObject].begin(); result != (*prevResults)[bestObject].end(); result++)
		{
			if (result->second)
				beat[result->first]++;
		}
	}

	for (auto firstPlayer = firstObjects->begin(); firstPlayer != firstObjects->end(); firstPlayer++)
	{
		for (auto secondPlayer = sample.begin(); secondPlayer != sample.end(); secondPlayer++)
		{
			if (*firstPlayer != *secondPlayer)
			{
				int result = simulationWorld->compareObjects(*firstPlayer, *secondPlayer);
				if (result != 0)
					setResult(*firstPlayer, *secondPlayer, result > 0);
			}
		}
	}
}


SharedSamplingCombiningStrategy::SharedSamplingCombiningStrategy(int amountOfCompetitionsPerObject_, SharedSamplingCombiningStrategy* otherCombiningStrategy_)
{
	otherCombiningStrategy = otherCombiningStrategy_;
	amountOfCompetitionsPerObject = amountOfCompetitionsPerObject_;
}

void SharedSamplingCombiningStrategy::setOtherCombiningStrategy(SharedSamplingCombiningStrategy* otherCombiningStrategy_)
{
	otherCombiningStrategy = otherCombiningStrategy_;
}