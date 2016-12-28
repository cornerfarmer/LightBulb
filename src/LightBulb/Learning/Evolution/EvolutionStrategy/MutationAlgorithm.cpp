// Includes
#include "LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include <math.h>
#include "LightBulb/LinearAlgebra/Matrix.hpp"

namespace LightBulb
{
	MutationAlgorithm::MutationAlgorithm(double mutationStrengthChangeSpeed_, double mutationStrengthMax_, double mutationStrengthMin_)
	{
		mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
		// Initialize the mutation strength boundaries
		mutationStrengthMax = mutationStrengthMax_;
		mutationStrengthMin = mutationStrengthMin_;
	}

	void MutationAlgorithm::execute(AbstractIndividual& individual1)
	{
		std::vector<double>& mutationStrength = individual1.getMutationStrength();

		// Go through all mutationStrength values
		for (auto mutationStrengthValue = mutationStrength.begin(); mutationStrengthValue != mutationStrength.end(); mutationStrengthValue++)
		{
			// Shrink or grow the mutationStrength randomly: *= exp(changeSpeed * random);
			*mutationStrengthValue *= exp(mutationStrengthChangeSpeed * zigguratGenerator->randDouble());
			// Make sure the values stays inside our boundaries
			*mutationStrengthValue = (*mutationStrengthValue < 0 ? -1 : 1) * std::min(mutationStrengthMax, std::max(mutationStrengthMin, std::abs(*mutationStrengthValue)));
		}

		std::vector<Matrix>& weights = individual1.getNeuralNetwork().getNetworkTopology().getAllWeights();
		int mutationStrengthIndex = 0;
		// Go through all edges
		for (auto layer = weights.begin(); layer != weights.end(); layer++)
		{
			for (int i = 0; i < layer->getEigenValue().rows(); i++)
			{
				for (int j = 0; j < layer->getEigenValue().cols(); j++)
				{
					// Simply add the corresponding mutationStrength value to the weight
					double weightAdd = mutationStrength[mutationStrengthIndex] * zigguratGenerator->randDouble();
					(*layer).getEigenValueForEditing()(i, j) += weightAdd;
					mutationStrengthIndex++;
				}
			}
		}

	}

	AbstractMutationAlgorithm* MutationAlgorithm::clone() const
	{
		return new MutationAlgorithm(*this);
	}

}

