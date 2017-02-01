// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/ConstantCoevolutionFitnessFunction.hpp"

namespace LightBulb
{
	std::map<const AbstractIndividual*, double>* ConstantCoevolutionFitnessFunction::execute(const CombiningStrategyResults& results)
	{
		std::map<const AbstractIndividual*, double>* fitnessValues = new std::map<const AbstractIndividual*, double>();

		for (auto resultsPerIndividual = results.begin(); resultsPerIndividual != results.end(); resultsPerIndividual++)
		{
			for (auto resultsPerCombination = resultsPerIndividual->second.begin(); resultsPerCombination != resultsPerIndividual->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (result->second)
						(*fitnessValues)[resultsPerIndividual->first]++;
				}
			}
		}

		return fitnessValues;
	}
}