// Includes
#include "Learning/Evolution/FitnessSharingFitnessFunction.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
// Library includes
#include <stdexcept>
#include <math.h>

FitnessSharingFitnessFunction::FitnessSharingFitnessFunction(double dissimilarityThreshold_, double exponent_)
{
	exponent = exponent_;
	dissimilarityThreshold = dissimilarityThreshold_;
}

void FitnessSharingFitnessFunction::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		double sharingValue = 1;

		for (auto otherEntry = highscore->begin(); otherEntry != highscore->end(); otherEntry++)
		{
			if (*otherEntry != *entry)
			{
				sharingValue += std::max(0.0, 1 - pow(entry->second->getNeuralNetwork()->getNetworkTopology()->calculateEuclideanDistance(*otherEntry->second->getNeuralNetwork()->getNetworkTopology()), exponent) / dissimilarityThreshold);
			}
		}

		entry->first = entry->first / sharingValue;
	}
}
