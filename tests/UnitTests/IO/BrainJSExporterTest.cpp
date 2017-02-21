#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/IO/Exporter/BrainJSExporter.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "gtest/gtest.h"

using namespace LightBulb;

TEST(BrainJSExporterTest, exportSimpleFeedForwardNetworkTopology)
{
	BrainJSExporter exporter;
	std::string expected = "{\"layers\":[{\"0\":{},\"1\":{}},{\"0\":{\"bias\":-5.97730827,\"weights\":{\"0\":-5.97730827,\"1\":-6.01825428}},\"1\":{\"bias\":-2.36775827,\"weights\":{\"0\":-2.36775827,\"1\":-2.46654963}},\"2\":{\"bias\":-2.84008765,\"weights\":{\"0\":-2.84008765,\"1\":-2.75312829}}},{\"0\":{\"bias\":-8.53883934,\"weights\":{\"0\":-8.53883934,\"1\":4.18224859,\"2\":4.96020699}}}]}";
	FeedForwardNetworkTopologyOptions options;
	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(3);
	options.neuronsPerLayerCount.push_back(1);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);
	auto& weights = networkTopology->getAllWeights();
	weights[0].getEigenValueForEditing()(0, 0) = -5.97730812;
	weights[0].getEigenValueForEditing()(0, 1) = -6.01825421;

	weights[0].getEigenValueForEditing()(1, 0) = -2.36775816;
	weights[0].getEigenValueForEditing()(1, 1) = -2.46654960;

	weights[0].getEigenValueForEditing()(2, 0) = -2.84008772;
	weights[0].getEigenValueForEditing()(2, 1) = -2.75312838;

	weights[1].getEigenValueForEditing()(0, 0) = -8.53883973;
	weights[1].getEigenValueForEditing()(0, 1) = 4.18224867;
	weights[1].getEigenValueForEditing()(0, 2) = 4.96020682;

	weights[0].getEigenValueForEditing()(0, 2) = 2.27842384;
	weights[0].getEigenValueForEditing()(1, 2) = 3.34858981;
	weights[0].getEigenValueForEditing()(2, 2) = 3.96418096;
	weights[1].getEigenValueForEditing()(0, 3) = -3.92979671;

	NeuralNetwork neuralNetwork(networkTopology);

	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	std::vector<double> output(1);
	neuralNetwork.calculate(input, output, TopologicalOrder());

	std::string result = exporter.exportToString(neuralNetwork);
	EXPECT_EQ(expected, result);
}
