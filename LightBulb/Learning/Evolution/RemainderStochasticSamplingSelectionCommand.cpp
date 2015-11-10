// Includes
#include "Learning/Evolution/RemainderStochasticSamplingSelectionCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
//Library includes
#include <iostream>
#include <iomanip>
#include <algorithm>

RemainderStochasticSamplingSelectionCommand::RemainderStochasticSamplingSelectionCommand(int objectCount_, bool enableDebugOutput_)
	: AbstractSelectionCommand(enableDebugOutput_)
{
	objectCount = objectCount_;
}


void RemainderStochasticSamplingSelectionCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	if (enableDebugOutput)
		std::cout << "Selected " << objectCount << " best ones:";
	
	double totalFitness = 0;

	// Go through all not selected objects
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		totalFitness += entry->first;
	}

	std::vector<std::pair<double, AbstractEvolutionObject*>> oldHighscore = *highscore;
	highscore->clear();

	std::vector<double> secondChance;

	for (auto entry = oldHighscore.begin(); entry != oldHighscore.end(); entry++)
	{
		int selectionCount = entry->first / totalFitness * objectCount;
		for (int i = 0; i < selectionCount; i++)
		{
			highscore->push_back(*entry);
		}
		secondChance.push_back(entry->first - selectionCount);
	}

	for (int i = 0; i < objectCount - highscore->size(); i++)
	{
		highscore->push_back(oldHighscore[randomFunction.execute(secondChance)]);
	}

	if (enableDebugOutput)
	{
		for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
		{
			std::cout << std::fixed << std::setprecision(5) << entry->first << ", ";
		}
	}

	if (enableDebugOutput)
		std::cout << std::endl;
}

void RemainderStochasticSamplingSelectionCommand::setObjectCount(int newObjectCount)
{
	objectCount = newObjectCount;
}
