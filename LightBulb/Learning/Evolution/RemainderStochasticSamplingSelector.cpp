// Includes
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
//Library includes
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

void RemainderStochasticSamplingSelector::select(bool recombination, int objectCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	double totalFitness = 0;

	// Go through all not selected objects
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		totalFitness += entry->first;
	}

	std::vector<double> secondChance;

	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		int selectionCount = entry->first / totalFitness * objectCount;
		for (int i = 0; i < selectionCount; i++)
		{
			if (recombination) 
				addObjectToRecombination(entry->second);
			else
				addObjectToMutate(entry->second);
		}
		if (withReplacement) {
			if (totalFitness != 0)
			{
				secondChance.push_back(entry->first / totalFitness * objectCount - selectionCount);
			}
			else
			{
				secondChance.push_back(0);
			}
		}
		else
			secondChance.push_back(entry->first);
	}

	while ((recombination && getRecombinationSelection()->size() < objectCount) || (!recombination && getMutationSelection()->size() < objectCount))
	{
		if (recombination)
			addObjectToRecombination((*highscore)[randomFunction.execute(secondChance)].second);
		else
			addObjectToMutate((*highscore)[randomFunction.execute(secondChance)].second);
	}
}

void RemainderStochasticSamplingSelector::selectForMutation(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	select(false, mutationCount, highscore);
}

void RemainderStochasticSamplingSelector::selectForRecombination(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	select(true, recombinationCount * 2, highscore);
	std::random_shuffle(getRecombinationSelection()->begin(), getRecombinationSelection()->end());
}

RemainderStochasticSamplingSelector::RemainderStochasticSamplingSelector(bool withReplacement_)
{
	withReplacement = withReplacement_;
}
