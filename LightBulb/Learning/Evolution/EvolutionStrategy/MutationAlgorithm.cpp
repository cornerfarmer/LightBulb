// Includes
#include "Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include <math.h>

namespace LightBulb
{
	MutationAlgorithm::MutationAlgorithm(double mutationStrengthChangeSpeed_, double mutationStrengthMax_, double mutationStrengthMin_)
	{
		mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
		// Initialize the mutation strength boundaries
		mutationStrengthMax = mutationStrengthMax_;
		mutationStrengthMin = mutationStrengthMin_;
	}

	void MutationAlgorithm::execute(AbstractEvolutionObject& object1)
	{
		std::vector<double>& mutationStrength = object1.getMutationStrength();

		// Go through all mutationStrength values
		for (auto mutationStrengthValue = mutationStrength.begin(); mutationStrengthValue != mutationStrength.end(); mutationStrengthValue++)
		{
			// Shrink or grow the mutationStrength randomly: *= exp(changeSpeed * random);
			*mutationStrengthValue *= exp(mutationStrengthChangeSpeed * generator.randDouble());
			// Make sure the values stays inside our boundaries
			*mutationStrengthValue = (*mutationStrengthValue < 0 ? -1 : 1) * std::min(mutationStrengthMax, std::max(mutationStrengthMin, std::abs(*mutationStrengthValue)));
		}

		std::vector<Eigen::MatrixXd>& weights = object1.getNeuralNetwork().getNetworkTopology().getAllWeights();
		int mutationStrengthIndex = 0;
		// Go through all edges
		for (auto layer = weights.begin(); layer != weights.end(); layer++)
		{
			for (int i = 0; i < layer->rows(); i++)
			{
				for (int j = 0; j < layer->cols(); j++)
				{
					// Simply add the corresponding mutationStrength value to the weight
					double weightAdd = mutationStrength[mutationStrengthIndex] * generator.randDouble();
					(*layer)(i, j) += weightAdd;
					mutationStrengthIndex++;
				}
			}
		}

	}

	AbstractMutationAlgorithm* MutationAlgorithm::clone() const
	{
		return new MutationAlgorithm(*this);
	}

	void MutationAlgorithm::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		generator.setSeed(randomGenerator_.getSeed());
	}

	void MutationAlgorithm::setMutationStrengthChangeSpeed(double mutationStrengthChangeSpeed_)
	{
		mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
	}


}

