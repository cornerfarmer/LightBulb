// Includes
#include "Learning/Evolution/MagnitudeBasedPruningMutationAlgorithm.hpp"
#include "AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

MagnitudeBasedPruningMutationAlgorithm::MagnitudeBasedPruningMutationAlgorithm(int removeNeuronsPerIteration_, int removeWeightsPerIteration_, bool useRandomFunction_, bool ignoreInputLayer_, bool removeNeuronsByTheirTotalWeight_)
{
	removeNeuronsPerIteration = removeNeuronsPerIteration_;
	removeWeightsPerIteration = removeWeightsPerIteration_;
	removeNeuronsByTheirTotalWeight = removeNeuronsByTheirTotalWeight_;
	useRandomFunction = useRandomFunction_;
	ignoreInputLayer = ignoreInputLayer_;
}

void MagnitudeBasedPruningMutationAlgorithm::execute(AbstractEvolutionObject* object1)
{
	auto networkTopology = object1->getNeuralNetwork()->getNetworkTopology();
	for (int n = 0; n < removeNeuronsPerIteration; n++)
	{
		bool usesBiasNeuron = networkTopology->usesBiasNeuron();
		std::vector<std::tuple<int, int, int>> neuronRanking;


		if (removeNeuronsByTheirTotalWeight)
		{
			auto weights = networkTopology->getWeights();
			int layerIndex = 0;
			for (auto layer = weights->begin(); layer != weights->end(); layer++, layerIndex++)
			{
				if (layerIndex > 0 || !ignoreInputLayer)
				{
					if (networkTopology->getNeuronCountInLayer(layerIndex) > 1)
					{
						auto weightSums = layer->cwiseAbs().colwise().sum();
						for (int i = usesBiasNeuron; i < weightSums.cols(); i++)
						{
							neuronRanking.push_back(std::make_tuple(weightSums[i], layerIndex, i));
						}
					}
				}
			}
		}
		else
		{
			auto weights = networkTopology->getWeights();
			int layerIndex = 0;
			for (auto layer = weights->begin(); layer != weights->end(); layer++, layerIndex++)
			{
				if (layerIndex > 0 || !ignoreInputLayer)
				{
					if (networkTopology->getNeuronCountInLayer(layerIndex) > 1)
					{
						for (int i = usesBiasNeuron; i < layer->cols(); i++)
						{
							int weightCount = 0;
							for (int j = 0; j < layer->rows(); j++)
							{
								if (networkTopology->existsAfferentWeight(layerIndex, i, j))
									weightCount++;
							}
							neuronRanking.push_back(std::make_tuple(weightCount, layerIndex, i));
						}
					}
				}
			}
		}

		if (neuronRanking.size() > 0) {

			std::sort(neuronRanking.begin(), neuronRanking.end(), std::less<std::tuple<int, int, int>>());

			int selectedIndex = 0;
			if (useRandomFunction)
				selectedIndex = randomFunction.execute(neuronRanking.size());

			networkTopology->removeNeuron(std::get<1>(neuronRanking[selectedIndex]), std::get<2>(neuronRanking[selectedIndex]));
		}
	}

	for (int w = 0; w < removeWeightsPerIteration; w++)
	{
		double minimalWeight = -1;
		int minimalWeightIndex = -1;
		int minimalWeightNeuronIndex = -1;
		int minimalWeightLayerIndex = -1;

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

		if (minimalWeightLayerIndex != -1)
			networkTopology->removeAfferentWeight(minimalWeightLayerIndex, minimalWeightNeuronIndex, minimalWeightIndex);
	}

	
}
