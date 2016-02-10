#include "NetworkPerformanceTests.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/BinaryFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include "NeuralNetwork/NeuralNetwork.hpp"

void doNetworkPerformanceTest()
{
	LayeredNetworkOptions LayeredNetworkOptions;
	LayeredNetworkOptions.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	LayeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	LayeredNetworkOptions.neuronsPerLayerCount[0] = 8;
	LayeredNetworkOptions.neuronsPerLayerCount[1] = 3;
	LayeredNetworkOptions.neuronsPerLayerCount[2] = 8;
	LayeredNetworkOptions.useBiasNeuron = true;

	LayeredNetwork layeredNetwork(LayeredNetworkOptions);

	NeuralNetwork neuralNetwork(&layeredNetwork);
	NeuralNetworkIO<double> input(8);
}