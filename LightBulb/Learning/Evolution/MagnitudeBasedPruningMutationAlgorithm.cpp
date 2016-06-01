// Includes
#include "Learning/Evolution/MagnitudeBasedPruningMutationAlgorithm.hpp"
#include "AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

MagnitudeBasedPruningMutationAlgorithm::MagnitudeBasedPruningMutationAlgorithm(int removeNeuronsPerIteration_, int removeWeightsPerIteration_, bool removeNeuronsByTheirTotalWeight_)
{
	removeNeuronsPerIteration = removeNeuronsPerIteration_;
	removeWeightsPerIteration = removeWeightsPerIteration_;
	removeNeuronsByTheirTotalWeight = removeNeuronsByTheirTotalWeight_;
}

void MagnitudeBasedPruningMutationAlgorithm::execute(AbstractEvolutionObject* object1)
{
	auto networkTopology = object1->getNeuralNetwork()->getNetworkTopology();
	for (int n = 0; n < removeNeuronsPerIteration; n++)
	{
		bool usesBiasNeuron = networkTopology->usesBiasNeuron();
		int minimalNeuronIndex;
		int minimalNeuronLayerIndex;

		if (removeNeuronsByTheirTotalWeight)
		{
			double minimalWeightSum = -1;

			auto weights = networkTopology->getWeights();
			int layerIndex = 0;
			for (auto layer = weights->begin(); layer != weights->end(); layer++, layerIndex++)
			{
				auto weightSums = layer->cwiseAbs().colwise().sum();
				for (int i = usesBiasNeuron; i < weightSums.cols(); i++)
				{
					if (weightSums[i] < minimalWeightSum || minimalWeightSum == -1)
					{
						minimalWeightSum = weightSums[i];
						minimalNeuronLayerIndex = layerIndex;
						minimalNeuronIndex = i;
					}
				}
			}
		}
		else
		{
			int minimalWeightCount = -1;

			auto weights = networkTopology->getWeights();
			int layerIndex = 0;
			for (auto layer = weights->begin(); layer != weights->end(); layer++, layerIndex++)
			{
				for (int i = usesBiasNeuron; i < layer->cols(); i++)
				{
					int weightCount = 0;
					for (int j = 0; j < layer->rows(); j++)
					{
						if (networkTopology->existsAfferentWeight(layerIndex, i, j))
							weightCount++;
					}
					if (weightCount < minimalWeightCount || minimalWeightCount == -1)
					{
						minimalWeightCount = weightCount;
						minimalNeuronLayerIndex = layerIndex;
						minimalNeuronIndex = i;
					}
				}
			}
		}

		networkTopology->removeNeuron(minimalNeuronLayerIndex, minimalNeuronIndex);
	}

	for (int w = 0; w < removeWeightsPerIteration; w++)
	{
		double minimalWeight = -1;
		int minimalWeightIndex;
		int minimalWeightNeuronIndex;
		int minimalWeightLayerIndex;

		auto weights = networkTopology->getWeights();
		int layerIndex = 0;
		for (auto layer = weights->begin(); layer != weights->end(); layer++, layerIndex++)
		{
			for (int i = 0; i < layer->rows(); i++)
			{
				for (int j = 0; j < layer->cols(); j++)
				{
					if (networkTopology->existsAfferentWeight(layerIndex, j, i) && (abs((*layer)(i, j)) < minimalWeight || minimalWeight == -1))
					{
						minimalWeight = abs((*layer)(i, j));
						minimalWeightLayerIndex = layerIndex;
						minimalWeightIndex = i;
						minimalWeightNeuronIndex = j;
					}
				}
			}
		}

		networkTopology->removeAfferentWeight(minimalWeightLayerIndex, minimalWeightNeuronIndex, minimalWeightIndex);
	}

	
}
