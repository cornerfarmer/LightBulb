#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "Mocks/MockNetworkTopology.hpp"
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "Mocks/MockNeuronDescription.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"

using namespace LightBulb;



class BackpropagationTest : public testing::Test {
public:
	MockNetworkTopology networkTopology;
	std::vector<Matrix<>> weights;
	std::vector<Matrix<>> weightsTransp;
	std::vector<Vector<>> netInputs;
	std::vector<Vector<>> activations;
	Vector<> errorVector;
	MockNeuronDescription neuronDescription;
	FermiFunction fermiFunction;

	void SetUp() {
		
		weights.resize(2);
		weights[0] = Matrix<>(3, 3);
		weights[0].getEigenValueForEditing() << 1, -2, 3,
			-4, 5, -6,
			7, -8, 9;
		weights[1] = Matrix<>(1, 4);
		weights[1].getEigenValueForEditing() << -1, 2, -3, 4;

		weightsTransp.resize(2);
		weightsTransp[0] = Matrix<>(weights[0].getEigenValueForEditing().transpose());
		weightsTransp[1] = Matrix<>(weights[1].getEigenValueForEditing().transpose());

		activations.resize(3);
		activations[0] = Vector<>(2);
		activations[0].getEigenValueForEditing() << 1, 0;
		activations[1] = Vector<>(3);
		activations[1].getEigenValueForEditing() << 0.982013762, 4.53978682e-05, 0.999999881;
		activations[2] = Vector<>(1);
		activations[2].getEigenValueForEditing() << 0.504519224;

		netInputs.resize(3);
		netInputs[1] = Vector<>(3);
		netInputs[1].getEigenValueForEditing() << 4, -10, 16;
		netInputs[2] = Vector<>(1);
		netInputs[2].getEigenValueForEditing() << 0.0180773735;

		errorVector = Vector<>(1);
		errorVector.getEigenValueForEditing() << 1 - 0.504519224;

		EXPECT_CALL(testing::Const(networkTopology), getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
		EXPECT_CALL(testing::Const(networkTopology), getAllNetInputs()).WillRepeatedly(testing::ReturnRef(netInputs));
		EXPECT_CALL(testing::Const(networkTopology), getAllActivations()).WillRepeatedly(testing::ReturnRef(activations));
		EXPECT_CALL(networkTopology, getEfferentWeightsPerLayer(0)).WillRepeatedly(testing::Return(weightsTransp[0]));
		EXPECT_CALL(networkTopology, getEfferentWeightsPerLayer(1)).WillRepeatedly(testing::Return(weightsTransp[1]));
		EXPECT_CALL(networkTopology, usesBiasNeuron()).WillRepeatedly(testing::Return(true));
		EXPECT_CALL(networkTopology, getLayerCount()).WillRepeatedly(testing::Return(3));
		EXPECT_CALL(networkTopology, getOutputNeuronDescription()).WillRepeatedly(testing::ReturnRef(neuronDescription));
		EXPECT_CALL(networkTopology, getInnerNeuronDescription()).WillRepeatedly(testing::ReturnRef(neuronDescription));
		EXPECT_CALL(neuronDescription, getActivationFunction()).WillRepeatedly(testing::ReturnRef(fermiFunction));


		
	}
};

TEST_F(BackpropagationTest, calcCorrectGradient)
{
	FeedForwardNetworkTopologyOptions options;
	options.neuronsPerLayerCount.resize(3);
	options.neuronsPerLayerCount[0] = 2;
	options.neuronsPerLayerCount[1] = 3;
	options.neuronsPerLayerCount[2] = 1;
	options.useBiasNeuron = true;
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction()));

	NeuralNetwork neuralNetwork(new FeedForwardNetworkTopology(options));
	
	neuralNetwork.getNetworkTopology().getAllWeights()[0].getEigenValueForEditing() << 1, -2, 3,
		-4, 5, -6,
		7, -8, 9;

	neuralNetwork.getNetworkTopology().getAllWeights()[1].getEigenValueForEditing() << -1, 2, -3, 4;


	std::vector<double> input(2);
	input[0] = 1;
	input[1] = 0;

	TopologicalOrder topologicalOrder;
	std::vector<double> output;
	Eigen::VectorXf errorVector(1);

	auto& weights = neuralNetwork.getNetworkTopology().getAllWeights();
	double epsilon = 0.0001;
	std::vector<Eigen::MatrixXd> gradientApprox(weights.size());
	for (int l = weights.size() - 1; l >= 0; l--)
	{
		gradientApprox[l].resizeLike(weights.at(l).getEigenValue());
		for (int n1 = 0; n1 < weights.at(l).getEigenValue().rows(); n1++)
		{
			for (int n2 = 0; n2 < weights.at(l).getEigenValue().cols(); n2++)
			{
				weights.at(l).getEigenValueForEditing()(n1, n2) += epsilon;
				output = neuralNetwork.calculate(input, topologicalOrder, true);
				errorVector(0) = 1 - output[0];
				double firstError = 0.5 * errorVector.cwiseAbs2().sum();

				weights.at(l).getEigenValueForEditing()(n1, n2) -= epsilon * 2;
				output = neuralNetwork.calculate(input, topologicalOrder, true);
				errorVector(0) = 1 - output[0];
				double secondError = 0.5 * errorVector.cwiseAbs2().sum();
				gradientApprox[l](n1, n2) = (firstError - secondError) / (2 * epsilon);

				weights.at(l).getEigenValueForEditing()(n1, n2) += epsilon;
			}
		}
	}


}

TEST_F(BackpropagationTest, calcGradient)
{

	Backpropagation backpropagation;

	backpropagation.initGradient(networkTopology);

	backpropagation.calcGradient(networkTopology, netInputs, activations, errorVector);

	std::vector<Matrix<>> expectedGradient;
	expectedGradient.resize(2);
	expectedGradient[0] = Matrix<>(3, 3);
	expectedGradient[0].getEigenValueForEditing() << 0.0021979212760925293, 0, 0.0021979212760925293,
		0, 0, 0,
		0, 0, 0;
	expectedGradient[1] = Matrix<>(1, 4);
	expectedGradient[1].getEigenValueForEditing() << -0.12166798114776611, 0, -0.12371689081192017, -0.12386590242385864;

	std::vector<Matrix<>>& gradient = backpropagation.getGradient();

	ASSERT_TRUE((gradient[0].getEigenValueForEditing() - expectedGradient[0].getEigenValueForEditing()).norm() < 1e-3);
	ASSERT_TRUE((gradient[1].getEigenValueForEditing() - expectedGradient[1].getEigenValueForEditing()).norm() < 1e-3);

}



TEST_F(BackpropagationTest, calcGradientGPU)
{

	Backpropagation backpropagation;
	backpropagation.setCalculatorType(CT_GPU);

	backpropagation.initGradient(networkTopology);

	backpropagation.calcGradient(networkTopology, netInputs, activations, errorVector);

	std::vector<Matrix<>> expectedGradient;
	expectedGradient.resize(2);
	expectedGradient[0] = Matrix<>(3, 3);
	expectedGradient[0].getEigenValueForEditing() << 0.0021979212760925293, 0, 0.0021979212760925293,
		0, 0, 0,
		0, 0, 0;
	expectedGradient[1] = Matrix<>(1, 4);
	expectedGradient[1].getEigenValueForEditing() << -0.12166798114776611, 0, -0.12371689081192017, -0.12386590242385864;

	std::vector<Matrix<>>& gradient = backpropagation.getGradient();
	gradient[0].getEigenValueForEditing();
	gradient[1].getEigenValueForEditing();

	ASSERT_TRUE((gradient[1].getEigenValueForEditing() - expectedGradient[1].getEigenValueForEditing()).norm() < 1e-3);
	ASSERT_TRUE((gradient[0].getEigenValueForEditing() - expectedGradient[0].getEigenValueForEditing()).norm() < 1e-3);

}


