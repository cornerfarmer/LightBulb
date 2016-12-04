// Includes
#include "LightBulb/Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

namespace LightBulb
{
	RecombinationAlgorithm::RecombinationAlgorithm(bool useAverageForWeight_, bool useAverageForMutationStrength_)
	{
		useAverageForWeight = useAverageForWeight_;
		useAverageForMutationStrength = useAverageForMutationStrength_;
	}

	void RecombinationAlgorithm::execute(AbstractIndividual& individual1, AbstractIndividual& individual2)
	{
		std::vector<Eigen::MatrixXd>& weights1 = static_cast<FeedForwardNetworkTopology&>(individual1.getNeuralNetwork().getNetworkTopology()).getAllWeights();
		std::vector<Eigen::MatrixXd>& weights2 = static_cast<FeedForwardNetworkTopology&>(individual2.getNeuralNetwork().getNetworkTopology()).getAllWeights();

		auto layer1 = weights1.begin();
		auto layer2 = weights2.begin();
		for (; layer1 != weights1.end(); layer1++, layer2++)
		{
			for (int i = 0; i < layer1->rows(); i++)
			{
				for (int j = 0; j < layer1->cols(); j++)
				{
					if (i < layer2->rows() && j < layer2->cols())
					{
						if (useAverageForWeight)
						{
							// Calculate the weights average and store it inside the first individual
							(*layer1)(i, j) = ((*layer1)(i, j) + (*layer2)(i, j)) / 2;
						}
						else
						{
							if (randomGenerator->randDouble() > 0.5)
								(*layer1)(i, j) = (*layer2)(i, j);
						}
					}
				}
			}
		}


		std::vector<double>& mutationStrength1 = individual1.getMutationStrength();
		std::vector<double>& mutationStrength2 = individual2.getMutationStrength();
		for (int i = 0; i < mutationStrength2.size() && i < mutationStrength1.size(); i++)
		{
			if (useAverageForMutationStrength)
			{
				mutationStrength1[i] = (mutationStrength2[i] + mutationStrength1[i]) / 2;
			}
			else
			{
				if (randomGenerator->randDouble() > 0.5)
					mutationStrength1[i] = mutationStrength2[i];
			}
		}
	}

	AbstractCloneable* RecombinationAlgorithm::clone() const
	{
		return new RecombinationAlgorithm(*this);
	}
}
