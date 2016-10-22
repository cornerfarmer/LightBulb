// Includes
#include "Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include <math.h>

namespace LightBulb
{
	MutationAlgorithm::MutationAlgorithm(double mutationStrengthChangeSpeed_)
	{
		mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
		// Initialize the mutation strength boundaries (TODO: Make them variable)
		mutationStrengthMax = 50;
		mutationStrengthMin = 0.000001f;
	}

	void MutationAlgorithm::execute(AbstractEvolutionObject* object1)
	{
		std::vector<double>* mutationStrength = object1->getMutationStrength();

		// Go through all mutationStrength values
		for (auto mutationStrengthValue = mutationStrength->begin(); mutationStrengthValue != mutationStrength->end(); mutationStrengthValue++)
		{
			// Shrink or grow the mutationStrength randomly: *= exp(changeSpeed * random);
			*mutationStrengthValue *= exp(mutationStrengthChangeSpeed * ZigguratGenerator::next());
			// Make sure the values stays inside our boundaries
			*mutationStrengthValue = (*mutationStrengthValue < 0 ? -1 : 1) * std::min(mutationStrengthMax, std::max(mutationStrengthMin, std::abs(*mutationStrengthValue)));
			// Change the mutation direction randomly (TODO: Make this variable)
			//if ((double)rand() / RAND_MAX > 0.5)
			//	*mutationStrengthValue *= -1;

		}

		std::vector<Eigen::MatrixXd>& weights = object1->getNeuralNetwork()->getNetworkTopology().getAllWeights();
		int mutationStrengthIndex = 0;
		// Go through all edges
		for (auto layer = weights.begin(); layer != weights.end(); layer++)
		{
			for (int i = 0; i < layer->rows(); i++)
			{
				for (int j = 0; j < layer->cols(); j++)
				{
					// Simply add the corresponding mutationStrength value to the weight (TODO: Maybe this step should be adjusted, because the original algorithm adds here an additional random factor)
					double weightAdd = (*mutationStrength)[mutationStrengthIndex] * ZigguratGenerator::next();
					(*layer)(i, j) += weightAdd;
					mutationStrengthIndex++;
				}
			}
		}

	}

	void MutationAlgorithm::setMutationStrengthChangeSpeed(double mutationStrengthChangeSpeed_)
	{
		mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
	}
}

