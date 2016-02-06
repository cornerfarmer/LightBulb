#include "gtest/gtest.h"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "IO/SynapticExporter.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Function/FermiFunction.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/IdentityFunction.hpp"
#include "Neuron/StandardThreshold.hpp"

TEST(SynapticExporterTest, exportSimpleLayeredNetwork)
{
	SynapticExporter exporter;
	std::string expected = "{\"neurons\":[{\"bias\":0.00000000000000,\"layer\":\"input\",\"squash\":\"HLIM\"},{\"bias\":0.00000000000000,\"layer\":\"input\",\"squash\":\"HLIM\"},{\"bias\":2.27842384712968,\"layer\":\"0\",\"squash\":\"HLIM\"},{\"bias\":3.34858981861236,\"layer\":\"0\",\"squash\":\"HLIM\"},{\"bias\":3.96418096172299,\"layer\":\"0\",\"squash\":\"HLIM\"},{\"bias\":-3.92979671193090,\"layer\":\"output\",\"squash\":\"HLIM\"}],\"connections\":[{\"from\":0,\"to\":2,\"weight\":-5.97730812726829},{\"from\":0,\"to\":3,\"weight\":-2.36775816488263},{\"from\":0,\"to\":4,\"weight\":-2.84008772426777},{\"from\":1,\"to\":2,\"weight\":-6.01825421209065},{\"from\":1,\"to\":3,\"weight\":-2.46654960015039},{\"from\":1,\"to\":4,\"weight\":-2.75312838822441},{\"from\":2,\"to\":5,\"weight\":-8.53883973729034},{\"from\":3,\"to\":5,\"weight\":4.18224867001210},{\"from\":4,\"to\":5,\"weight\":4.96020682361533}]}";
	LayeredNetworkOptions options;
	options.neuronsPerLayerCount.push_back(2);
	options.neuronsPerLayerCount.push_back(3);
	options.neuronsPerLayerCount.push_back(1);
	options.activationFunction = new FermiFunction(1);
	options.inputFunction = new WeightedSumFunction();
	options.outputFunction = new IdentityFunction();
	options.threshold = new StandardThreshold(0);
	options.useBiasNeuron = true;
	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);
	auto weights = layeredNetwork->getWeights();
	/*(*weights)[0][0] = -5.97730812726829;
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
	(*weights)[6][5] = -3.92979671193090;*/

	NeuralNetwork neuralNetwork(layeredNetwork);

	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	std::vector<double> output(1);
	neuralNetwork.calculate(input, output, TopologicalOrder());

	std::string result = exporter.execute(&neuralNetwork);
	EXPECT_EQ(expected, result);
}
