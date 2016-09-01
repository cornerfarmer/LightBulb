#include "NetworkPerformanceTests.hpp"
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuronFactory/SameNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <Function/ActivationFunction/BinaryFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include <ctime>
#include <iostream>
#include <iomanip>

void doNetworkPerformanceTest()
{
	FeedForwardNetworkTopologyOptions FeedForwardNetworkTopologyOptions;
	FeedForwardNetworkTopologyOptions.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	FeedForwardNetworkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[0] = 8;
	FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[1] = 3;
	FeedForwardNetworkTopologyOptions.neuronsPerLayerCount[2] = 8;

	FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(FeedForwardNetworkTopologyOptions);

	NeuralNetwork neuralNetwork(networkTopology);
	std::vector<double> input(8);
	std::vector<double> output(8);
	TopologicalOrder activationOrder;
	clock_t begin = clock();
	for (int i = 0; i < 1000000; i++) {
		neuralNetwork.calculate(input, output, activationOrder);
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time:" << std::fixed << std::setprecision(4) << elapsed_secs << std::endl;
}
