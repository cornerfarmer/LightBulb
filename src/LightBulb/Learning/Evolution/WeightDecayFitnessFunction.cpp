// Includes
#include "LightBulb/Learning/Evolution/WeightDecayFitnessFunction.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

// Library includes

namespace LightBulb
{
	WeightDecayFitnessFunction::WeightDecayFitnessFunction(double fac_)
	{
		fac = fac_;
	}

	void WeightDecayFitnessFunction::execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			double weightDecayError = 0;
			std::vector<Matrix>& weights = entry->second->getNeuralNetwork().getNetworkTopology().getAllWeights();
			for (auto weightsPerLayer = weights.begin(); weightsPerLayer != weights.end(); weightsPerLayer++)
			{
				weightDecayError += 0.5 * weightsPerLayer->getEigenValue().squaredNorm();
			}

			entry->first -= fac * weightDecayError;
		}
		sort(highscore.begin(), highscore.end(), std::greater<std::pair<double, AbstractIndividual*>>());
	}

	AbstractFitnessFunction* WeightDecayFitnessFunction::clone() const
	{
		return new WeightDecayFitnessFunction(*this);
	}
}
