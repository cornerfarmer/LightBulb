// Includes
#include "Learning/Evolution/ConstantCoevolutionFitnessFunction.hpp"

std::map<AbstractEvolutionObject*, double> ConstantCoevolutionFitnessFunction::execute(std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& results)
{
	std::map<AbstractEvolutionObject*, double> fitnessValues;

	for (auto resultsPerObject = results.begin(); resultsPerObject != results.end(); resultsPerObject++)
	{
		for (auto result = resultsPerObject->second.begin(); result != resultsPerObject->second.end(); result++)
		{
			if (result->second)
				fitnessValues[resultsPerObject->first]++;
		}
	}

	return fitnessValues;
}