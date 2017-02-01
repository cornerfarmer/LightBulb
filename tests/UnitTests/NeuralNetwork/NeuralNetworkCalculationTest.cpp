#include "UnitTestsPrec.hpp"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "Mocks/MockNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"

using namespace LightBulb;



class NeuralNetworkCalculationTest : public testing::Test {
public:
	NeuralNetwork* neuralNetwork;
	std::vector<Vector<>> expectedAct;
	std::vector<Vector<>> expectedNetInput;

	void SetUp() {
		FeedForwardNetworkTopologyOptions options;
		options.neuronsPerLayerCount.resize(3);
		options.neuronsPerLayerCount[0] = 2;
		options.neuronsPerLayerCount[1] = 3;
		options.neuronsPerLayerCount[2] = 1;
		options.useBiasNeuron = true;
		options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction()));

		neuralNetwork = new NeuralNetwork(new FeedForwardNetworkTopology(options));

		neuralNetwork->getNetworkTopology().getAllWeights()[0].getEigenValueForEditing() << 1, -2, 3,
			-4, 5, -6,
			7, -8, 9;

		neuralNetwork->getNetworkTopology().getAllWeights()[1].getEigenValueForEditing() << -1, 2, -3, 4;
		

		expectedAct.resize(3);
		expectedAct[0] = Vector<>(3);
		expectedAct[0].getEigenValueForEditing() << 1, 0, 1;
		expectedAct[1] = Vector<>(4);
		expectedAct[1].getEigenValueForEditing() << 0.982013762, 4.53978682e-05, 0.999999881, 1;
		expectedAct[2] = Vector<>(2);
		expectedAct[2].getEigenValueForEditing() << 0.504519224, 1;

		expectedNetInput.resize(3);
		expectedNetInput[1] = Vector<>(3);
		expectedNetInput[1].getEigenValueForEditing() << 4, -10, 16;
		expectedNetInput[2] = Vector<>(1);
		expectedNetInput[2].getEigenValueForEditing() << 0.0180773735;
	}
};


TEST_F(NeuralNetworkCalculationTest, adjustWeights)
{	
	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	TopologicalOrder topologicalOrder;

	std::vector<double> output = neuralNetwork->calculate(input, topologicalOrder, true);
		
	ASSERT_EQ(0.50451922416687012, output[0]);
	ASSERT_EQ(expectedAct[0].getEigenValue(), neuralNetwork->getNetworkTopology().getAllActivations()[0].getEigenValue());
	ASSERT_EQ(expectedAct[1].getEigenValue(), neuralNetwork->getNetworkTopology().getAllActivations()[1].getEigenValue());
	ASSERT_EQ(expectedAct[2].getEigenValue(), neuralNetwork->getNetworkTopology().getAllActivations()[2].getEigenValue());

	ASSERT_EQ(expectedNetInput[1].getEigenValue(), neuralNetwork->getNetworkTopology().getAllNetInputs()[1].getEigenValue());
	ASSERT_EQ(expectedNetInput[2].getEigenValue(), neuralNetwork->getNetworkTopology().getAllNetInputs()[2].getEigenValue());

}


TEST_F(NeuralNetworkCalculationTest, adjustWeightsGPU)
{
	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	TopologicalOrder topologicalOrder;

	neuralNetwork->getNetworkTopology().setCalculatorType(CT_GPU);
	std::vector<double> output = neuralNetwork->calculate(input, topologicalOrder, true);

	ASSERT_EQ(0.50451922416687012, output[0]);
	ASSERT_EQ(expectedAct[0].getEigenValue(), neuralNetwork->getNetworkTopology().getAllActivations()[0].getEigenValue());
	ASSERT_EQ(expectedAct[1].getEigenValue(), neuralNetwork->getNetworkTopology().getAllActivations()[1].getEigenValue());
	ASSERT_EQ(expectedAct[2].getEigenValue(), neuralNetwork->getNetworkTopology().getAllActivations()[2].getEigenValue());

	ASSERT_EQ(expectedNetInput[1].getEigenValue(), neuralNetwork->getNetworkTopology().getAllNetInputs()[1].getEigenValue());
	ASSERT_EQ(expectedNetInput[2].getEigenValue(), neuralNetwork->getNetworkTopology().getAllNetInputs()[2].getEigenValue());

}

