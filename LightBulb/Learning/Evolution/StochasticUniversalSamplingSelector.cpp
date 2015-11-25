// Includes
#include <Learning/Evolution/StochasticUniversalSamplingSelector.hpp>.hpp>
//Library includes
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

void StochasticUniversalSamplingSelector::initMutation(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int mutationCount)
{
	if (highscore->size() == 0)
		throw std::invalid_argument("The given highscore is empty!");

	objectSequence.resize(mutationCount);
	
	if (mutationCount > 0)
	{
		std::vector<double> probabilities;
		probabilities.reserve(highscore->size());

		for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
		{
			probabilities.push_back(entry->first);
		}

		std::vector<int> selectedIndices = randomFunction.execute(probabilities, mutationCount);
		int mutationSequenceIndex = 0;
		for (auto selectedIndex = selectedIndices.begin(); selectedIndex != selectedIndices.end(); selectedIndex++, mutationSequenceIndex++)
		{
			objectSequence[mutationSequenceIndex] = (*highscore)[*selectedIndex].second;
		}
	}

	if (objectSequence.size() != mutationCount)
		throw std::logic_error("The RemainderStochasticSamplingSelector initialization was not successful");

	currentObjectIndex = 0;
}

void StochasticUniversalSamplingSelector::initRecombination(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int recombinationCount)
{
	initMutation(highscore, recombinationCount * 2);
	std::random_shuffle(objectSequence.begin(), objectSequence.end());
}

AbstractEvolutionObject* StochasticUniversalSamplingSelector::nextMutation()
{
	return objectSequence[currentObjectIndex++];
}

std::array<AbstractEvolutionObject*, 2> StochasticUniversalSamplingSelector::nextRecombination()
{
	std::array<AbstractEvolutionObject*, 2> arr;
	arr[0] = objectSequence[currentObjectIndex++];
	arr[1] = objectSequence[currentObjectIndex++];
	return arr;
}

bool StochasticUniversalSamplingSelector::hasFinished()
{
	return currentObjectIndex == objectSequence.size();
}
