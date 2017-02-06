// Includes
#include "LightBulb/Learning/Evolution/ConstantCoevolutionFitnessFunction.hpp"
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	std::map<const AbstractIndividual*, double>* ConstantCoevolutionFitnessFunction::execute(const CombiningStrategyResults& results)
	{
		std::map<const AbstractIndividual*, double>* fitnessValues = new std::map<const AbstractIndividual*, double>();

		for (auto resultsPerIndividual = results.matchIndices.begin(); resultsPerIndividual != results.matchIndices.end(); resultsPerIndividual++)
		{
			for (auto resultsPerCombination = resultsPerIndividual->second.begin(); resultsPerCombination != resultsPerIndividual->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (results.resultVector.getEigenValue()[result->second])
						(*fitnessValues)[resultsPerIndividual->first]++;
				}
			}
		}

		return fitnessValues;
	}
}
