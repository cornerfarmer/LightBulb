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
	std::string expected = "{\"layers\":[{\"0\":{},\"1\":{}},{\"0\":{\"bias\":2.27842384712968,\"weights\":{\"0\":-5.97730812726829,\"1\":-6.01825421209065}},\"1\":{\"bias\":3.34858981861236,\"weights\":{\"0\":-2.36775816488263,\"1\":-2.46654960015039}},\"2\":{\"bias\":3.96418096172299,\"weights\":{\"0\":-2.84008772426777,\"1\":-2.75312838822441}}},{\"0\":{\"bias\":-3.92979671193090,\"weights\":{\"0\":-8.53883973729034,\"1\":4.18224867001210,\"2\":4.96020682361533}}}]}";
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
	(*weights)[0][0] = -5.97730812726829;
	(*weights)[0][1] = -2.36775816488263;
	(*weights)[0][2] = -2.84008772426777;

	(*weights)[1][0] = -6.01825421209065;
	(*weights)[1][1] = -2.46654960015039;
	(*weights)[1][2] = -2.75312838822441;

	(*weights)[2][0] = -8.53883973729034;
	(*weights)[3][0] = 4.18224867001210;
	(*weights)[4][0] = 4.96020682361533;

	(*weights)[6][2] = 2.27842384712968;
	(*weights)[6][3] = 3.34858981861236;
	(*weights)[6][4] = 3.96418096172299;
	(*weights)[6][5] = -3.92979671193090;

	NeuralNetwork neuralNetwork(layeredNetwork);

	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	std::vector<double> output(1);
	neuralNetwork.calculate(input, output, TopologicalOrder());

	std::string result = exporter.execute(&neuralNetwork);
	EXPECT_EQ(expected, result);
}
