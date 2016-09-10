// Includes
#include "Learning/Evolution/SharedCoevolutionFitnessFunction.hpp"

namespace LightBulb
{
	std::map<AbstractEvolutionObject*, double>* SharedCoevolutionFitnessFunction::execute(CombiningStrategyResults& results)
	{
		std::map<AbstractEvolutionObject*, std::map<int, int>> winCounter;

		for (auto resultsPerObject = results.begin(); resultsPerObject != results.end(); resultsPerObject++)
		{
			for (auto resultsPerCombination = resultsPerObject->second.begin(); resultsPerCombination != resultsPerObject->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (result->second)
						winCounter[resultsPerCombination->first][result->first]++;
				}
			}
		}

		std::map<AbstractEvolutionObject*, double>* fitnessValues = new std::map<AbstractEvolutionObject*, double>();

		for (auto resultsPerObject = results.begin(); resultsPerObject != results.end(); resultsPerObject++)
		{
			for (auto resultsPerCombination = resultsPerObject->second.begin(); resultsPerCombination != resultsPerObject->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (result->second)
					{
						(*fitnessValues)[resultsPerObject->first] += 1.0 / winCounter[resultsPerCombination->first][result->first];
					}
				}
			}
		}

		return fitnessValues;
	}
}