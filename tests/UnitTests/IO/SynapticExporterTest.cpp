#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/IO/Exporter/SynapticExporter.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Function/ActivationFunction/BinaryFunction.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "gtest/gtest.h"

using namespace LightBulb;

TEST(SynapticExporterTest, exportSimpleFeedForwardNetworkTopology)
{
	SynapticExporter exporter;
	std::string expected = "{\"neurons\":[{\"bias\":0.00000000000000,\"layer\":\"input\",\"squash\":\"HLIM\"},{\"bias\":0.00000000000000,\"layer\":\"input\",\"squash\":\"HLIM\"},{\"bias\":-5.97730812726829,\"layer\":\"0\",\"squash\":\"HLIM\"},{\"bias\":-2.36775816488263,\"layer\":\"0\",\"squash\":\"HLIM\"},{\"bias\":-2.84008772426777,\"layer\":\"0\",\"squash\":\"HLIM\"},{\"bias\":-8.53883973729034,\"layer\":\"output\",\"squash\":\"HLIM\"}],\"connections\":[{\"from\":0,\"to\":2,\"weight\":-6.01825421209065},{\"from\":0,\"to\":3,\"weight\":-2.46654960015039},{\"from\":0,\"to\":4,\"weight\":-2.75312838822441},{\"from\":1,\"to\":2,\"weight\":2.27842384712968},{\"from\":1,\"to\":3,\"weight\":3.34858981861236},{\"from\":1,\"to\":4,\"weight\":3.96418096172299},{\"from\":2,\"to\":5,\"weight\":4.18224867001210},{\"from\":3,\"to\":5,\"weight\":4.96020682361533},{\"from\":4,\"to\":5,\"weight\":-3.92979671193090}]}";
	FeedForwardNetworkTopologyOptions options;
	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(3);
	options.neuronsPerLayerCount.push_back(1);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);
	auto& weights = networkTopology->getAllWeights();
	weights[0].getEigenValueForEditing()(0, 0) = -5.97730812726829;
	weights[0].getEigenValueForEditing()(0, 1) = -6.01825421209065;

	weights[0].getEigenValueForEditing()(1, 0) = -2.36775816488263;
	weights[0].getEigenValueForEditing()(1, 1) = -2.46654960015039;

	weights[0].getEigenValueForEditing()(2, 0) = -2.84008772426777;
	weights[0].getEigenValueForEditing()(2, 1) = -2.75312838822441;

	weights[1].getEigenValueForEditing()(0, 0) = -8.53883973729034;
	weights[1].getEigenValueForEditing()(0, 1) = 4.18224867001210;
	weights[1].getEigenValueForEditing()(0, 2) = 4.96020682361533;

	weights[0].getEigenValueForEditing()(0, 2) = 2.27842384712968;
	weights[0].getEigenValueForEditing()(1, 2) = 3.34858981861236;
	weights[0].getEigenValueForEditing()(2, 2) = 3.96418096172299;
	weights[1].getEigenValueForEditing()(0, 3) = -3.92979671193090;

	NeuralNetwork neuralNetwork(networkTopology);

	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	std::vector<double> output(1);
	neuralNetwork.calculate(input, output, TopologicalOrder());

	std::string result = exporter.exportToString(neuralNetwork);
	EXPECT_EQ(expected, result);
}
