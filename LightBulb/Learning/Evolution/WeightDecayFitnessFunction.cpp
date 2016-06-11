// Includes
#include "Learning/Evolution/WeightDecayFitnessFunction.hpp"
#include "AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

// Library includes

WeightDecayFitnessFunction::WeightDecayFitnessFunction(double fac_)
{
	fac = fac_;
}

void WeightDecayFitnessFunction::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		double weightDecayError = 0;
		auto weights = entry->second->getNeuralNetwork()->getNetworkTopology()->getWeights();
		for (auto weightsPerLayer = weights->begin(); weightsPerLayer != weights->end(); weightsPerLayer++)
		{
			weightDecayError += 0.5 * weightsPerLayer->squaredNorm();
		}
		
		entry->first -= fac * weightDecayError;
	}
}