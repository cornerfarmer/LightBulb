// Includes
#include "Learning/Evolution/SharedCoevolutionFitnessFunction.hpp"

std::map<AbstractEvolutionObject*, double>* SharedCoevolutionFitnessFunction::execute(std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>>& results)
{
	std::map<AbstractEvolutionObject*, int> winCounter;

	for (auto resultsPerObject = results.begin(); resultsPerObject != results.end(); resultsPerObject++)
	{
		for (auto result = resultsPerObject->second.begin(); result != resultsPerObject->second.end(); result++)
		{
			if (result->second)
				winCounter[result->first]++;
		}
	}

	std::map<AbstractEvolutionObject*, double>* fitnessValues = new std::map<AbstractEvolutionObject*, double>();

	for (auto resultsPerObject = results.begin(); resultsPerObject != results.end(); resultsPerObject++)
	{
		for (auto result = resultsPerObject->second.begin(); result != resultsPerObject->second.end(); result++)
		{
			if (result->second)
			{
				(*fitnessValues)[resultsPerObject->first] += 1.0 / winCounter[result->first];
			}
		}
	}

	return fitnessValues;
}