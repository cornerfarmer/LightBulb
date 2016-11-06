// Includes
#include "Learning/Evolution/ConstantCoevolutionFitnessFunction.hpp"
#include "AbstractCoevolutionWorld.hpp"

namespace LightBulb
{
	std::map<const AbstractEvolutionObject*, double>* ConstantCoevolutionFitnessFunction::execute(const CombiningStrategyResults& results)
	{
		std::map<const AbstractEvolutionObject*, double>* fitnessValues = new std::map<const AbstractEvolutionObject*, double>();

		for (auto resultsPerObject = results.begin(); resultsPerObject != results.end(); resultsPerObject++)
		{
			for (auto resultsPerCombination = resultsPerObject->second.begin(); resultsPerCombination != resultsPerObject->second.end(); resultsPerCombination++)
			{
				for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
				{
					if (result->second)
						(*fitnessValues)[resultsPerObject->first]++;
				}
			}
		}

		return fitnessValues;
	}
}