// Includes
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
//Library includes
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

RemainderStochasticSamplingSelector::RemainderStochasticSamplingSelector(bool withReplacement_)
{
	withReplacement = withReplacement_;
}

void RemainderStochasticSamplingSelector::initMutation(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int mutationCount)
{
	if (highscore->size() == 0)
		throw std::invalid_argument("The given highscore is empty!");

	objectSequence.resize(mutationCount);
	

	double totalFitness = 0;

	// Go through all not selected objects
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		totalFitness += entry->first;
	}

	std::vector<double> secondChance;
	int mutationSequenceIndex = 0;


	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		int selectionCount = entry->first / totalFitness * mutationCount;
		for (int i = 0; i < selectionCount; i++)
		{
		 	objectSequence[mutationSequenceIndex++] = entry->second;
		}
		if (withReplacement)
			secondChance.push_back(entry->first / totalFitness * mutationCount - selectionCount);
		else
			secondChance.push_back(entry->first);
	}


	for (; mutationSequenceIndex < objectSequence.size(); mutationSequenceIndex++)
	{
		objectSequence[mutationSequenceIndex] = (*highscore)[randomFunction.execute(secondChance)].second;
	}

	if (objectSequence.size() != mutationCount)
		throw std::logic_error("The RemainderStochasticSamplingSelector initialization was not successful");

	currentObjectIndex = 0;
}

void RemainderStochasticSamplingSelector::initRecombination(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int recombinationCount)
{
	initMutation(highscore, recombinationCount * 2);
	std::random_shuffle(objectSequence.begin(), objectSequence.end());
}

AbstractEvolutionObject* RemainderStochasticSamplingSelector::nextMutation()
{
	return objectSequence[currentObjectIndex++];
}

std::array<AbstractEvolutionObject*, 2> RemainderStochasticSamplingSelector::nextRecombination()
{
	std::array<AbstractEvolutionObject*, 2> arr;
	arr[0] = objectSequence[currentObjectIndex++];
	arr[1] = objectSequence[currentObjectIndex++];
	return arr;
}

bool RemainderStochasticSamplingSelector::hasFinished()
{
	return currentObjectIndex == objectSequence.size();
}
