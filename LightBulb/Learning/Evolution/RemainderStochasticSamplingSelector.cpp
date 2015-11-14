// Includes
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
//Library includes
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

void RemainderStochasticSamplingSelector::initMutation(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int mutationCount)
{
	if (highscore->size() == 0)
		throw std::invalid_argument("The given highscore is empty!");

	objectSequence.resize(mutationCount);
	
	double smallestFitness = highscore->front().first;
	// Go through all not selected objects
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		if (smallestFitness > entry->first)
			smallestFitness = entry->first;
	}

	double totalFitnessDistance = 0;

	// Go through all not selected objects
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		totalFitnessDistance += entry->first - smallestFitness;
	}

	std::vector<double> secondChance;
	int mutationSequenceIndex = 0;


	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		double selectionCount = 0;
		if (totalFitnessDistance > 0)
			selectionCount = (entry->first - smallestFitness) / totalFitnessDistance * mutationCount;

		for (int i = 0; i < (int)selectionCount; i++)
		{
			objectSequence[mutationSequenceIndex++] = entry->second;
		}
		secondChance.push_back(std::max(0.0001, selectionCount - (int)selectionCount));
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
	return std::array<AbstractEvolutionObject*, 2> { objectSequence[currentObjectIndex++], objectSequence[currentObjectIndex++] };
}

bool RemainderStochasticSamplingSelector::hasFinished()
{
	return currentObjectIndex == objectSequence.size();
}
