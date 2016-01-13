#include "gtest/gtest.h"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "IO/BrainJSExporter.hpp"
#include "NetworkTopology/FastLayeredNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Function\FermiFunction.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\IdentityFunction.hpp"
#include "Neuron\StandardThreshold.hpp"

TEST(exportSimpleLayeredNetwork, BrainJSExporterTest)
{
	BrainJSExporter exporter;
	std::string expected = "{\"layers\":[{\"0\":{},\"1\":{}},{\"0\":{\"bias\":2.27842384712968,\"weights\":{\"0\":-5.977308127268292,\"1\":-6.018254212090658}},\"1\":{\"bias\":3.348589818612367,\"weights\":{\"0\":-2.3677581648826327,\"1\":-2.4665496001503926}},\"2\":{\"bias\":3.964180961722991,\"weights\":{\"0\":-2.8400877242677716,\"1\":-2.7531283882244133}}},{\"0\":{\"bias\":-3.929796711930905,\"weights\":{\"0\":-8.538839737290349,\"1\":4.1822486700121075,\"2\":4.960206823615332}}}],\"outputLookup\":false,\"inputLookup\":false}";
	FastLayeredNetworkOptions options;
	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(3);
	options.neuronsPerLayerCount.push_back(1);
	options.activationFunction = new FermiFunction(1);
	options.inputFunction = new WeightedSumFunction();
	options.outputFunction = new IdentityFunction();
	options.threshold = new StandardThreshold(0);
	options.useBiasNeuron = true;
	FastLayeredNetwork* layeredNetwork = new FastLayeredNetwork(options);
	auto weights = layeredNetwork->getWeights();
	(*weights)[0][0] = -5.977308127268292;
	(*weights)[0][1] = -2.3677581648826327;
	(*weights)[0][2] = -2.8400877242677716;

	(*weights)[1][0] = -6.018254212090658;
	(*weights)[1][1] = -2.4665496001503926;
	(*weights)[1][2] = -2.7531283882244133;

	(*weights)[2][0] = -8.538839737290349;
	(*weights)[3][0] = 4.1822486700121075;
	(*weights)[4][0] = 4.960206823615332;

	(*weights)[6][2] = 2.27842384712968;
	(*weights)[6][3] = 3.348589818612367;
	(*weights)[6][4] = 3.964180961722991;
	(*weights)[6][5] = -3.929796711930905;

	NeuralNetwork neuralNetwork(layeredNetwork);

	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	std::vector<double> output(1);
	neuralNetwork.calculate(input, output, TopologicalOrder());

	std::string result = exporter.execute(&neuralNetwork);
	EXPECT_EQ(expected, result);
}
