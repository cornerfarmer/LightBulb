// Includes
#include "LightBulb/Learning/Evolution/SharedCoevolutionFitnessFunction.hpp"
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	std::map<const AbstractIndividual*, double>* SharedCoevolutionFitnessFunction::execute(const CombiningStrategyResults& results)
	{
		std::map<AbstractIndividual*, std::map<int, int>> winCounter;

		for (auto resultsPerIndividual = results.matchIndices.begin(); resultsPerIndividual != results.matchIndices.end(); resultsPerIndividual++)
		{
			for (auto resultsPerCombination = resultsPerIndividual->second.begin(); resultsPerCombination != resultsPerIndividual->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (results.resultVector.getEigenValue()[result->second])
						winCounter[resultsPerCombination->first][result->first]++;
				}
			}
		}

		std::map<const AbstractIndividual*, double>* fitnessValues = new std::map<const AbstractIndividual*, double>();

		for (auto resultsPerIndividual = results.matchIndices.begin(); resultsPerIndividual != results.matchIndices.end(); resultsPerIndividual++)
		{
			for (auto resultsPerCombination = resultsPerIndividual->second.begin(); resultsPerCombination != resultsPerIndividual->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (results.resultVector.getEigenValue()[result->second])
					{
						(*fitnessValues)[resultsPerIndividual->first] += 1.0 / winCounter[resultsPerCombination->first][result->first];
					}
				}
			}
		}

		return fitnessValues;
	}
}
