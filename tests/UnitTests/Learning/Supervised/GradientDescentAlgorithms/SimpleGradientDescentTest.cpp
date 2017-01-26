#include "gtest/gtest.h"
#include "LightBulb/Function/InputFunction/WeightedSumFunction.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"
#include "Mocks/MockNetworkTopology.hpp"

using namespace LightBulb;



class SimpleGradientDescentTest : public testing::Test {
public:
	MockNetworkTopology networkTopology;
	std::vector<Matrix<>> weights;
	std::vector<Matrix<>> gradients;

	void SetUp() {
		weights.resize(2);
		gradients.resize(2);
		
		weights[0] = Matrix<>(3, 3);
		weights[0].getEigenValueForEditing() << 1, 2, 3,
			4, 5, 6,
			7, 8, 9;
		weights[1] = Matrix<>(1, 4);
		weights[1].getEigenValueForEditing() << 1, 2, 3, 4;

		
		gradients[0] = Matrix<>(3, 3);
		gradients[0].getEigenValueForEditing() << 3, 2, 1,
			6, 5, 4,
			9, 8, 7;
		gradients[1] = Matrix<>(1, 4);
		gradients[1].getEigenValueForEditing() << 4, 3, 2, 1;

		EXPECT_CALL(testing::Const(networkTopology), getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));
	}
};


TEST_F(SimpleGradientDescentTest, adjustWeights)
{
	SimpleGradientDescentOptions options;
	options.momentum = 0;
	options.learningRate = 0.5;
	options.weightDecayFac = 0;

	SimpleGradientDescent simpleGradientDescent(options);

	simpleGradientDescent.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	simpleGradientDescent.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	std::vector<Matrix<>> weightsExpected(2);
	weightsExpected[0] = Matrix<>(3, 3);
	weightsExpected[0].getEigenValueForEditing() << -0.5, 1, 2.5,
		1, 2.5, 4,
		2.5, 4, 5.5;
	weightsExpected[1] = Matrix<>(1, 4);
	weightsExpected[1].getEigenValueForEditing() << -1, 0.5, 2, 3.5;

	ASSERT_EQ(weightsExpected[0].getEigenValue(), weights[0].getEigenValue());
	ASSERT_EQ(weightsExpected[1].getEigenValue(), weights[1].getEigenValue());
}


TEST_F(SimpleGradientDescentTest, adjustWeightsGPU)
{
	SimpleGradientDescentOptions options;
	options.momentum = 0;
	options.learningRate = 0.5;
	options.weightDecayFac = 0;

	SimpleGradientDescent simpleGradientDescent(options);

	simpleGradientDescent.setCalculatorType(CT_GPU);

	simpleGradientDescent.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	simpleGradientDescent.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	std::vector<Matrix<>> weightsExpected(2);
	weightsExpected[0] = Matrix<>(3, 3);
	weightsExpected[0].getEigenValueForEditing() << -0.5, 1, 2.5,
		1, 2.5, 4,
		2.5, 4, 5.5;
	weightsExpected[1] = Matrix<>(1, 4);
	weightsExpected[1].getEigenValueForEditing() << -1, 0.5, 2, 3.5;

	ASSERT_EQ(weightsExpected[0].getEigenValue(), weights[0].getEigenValue());
	ASSERT_EQ(weightsExpected[1].getEigenValue(), weights[1].getEigenValue());
}




TEST_F(SimpleGradientDescentTest, adjustWeightsWithMomentum)
{
	SimpleGradientDescentOptions options;
	options.momentum = 0.5;
	options.learningRate = 0.5;
	options.weightDecayFac = 0;

	SimpleGradientDescent simpleGradientDescent(options);

	simpleGradientDescent.initializeAlgorithm(networkTopology);

	simpleGradientDescent.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	simpleGradientDescent.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	std::vector<Matrix<>> weightsExpected(2);
	weightsExpected[0] = Matrix<>(3, 3);
	weightsExpected[0].getEigenValueForEditing() << -0.5, 1, 2.5,
		1, 2.5, 4,
		2.5, 4, 5.5;
	weightsExpected[1] = Matrix<>(1, 4);
	weightsExpected[1].getEigenValueForEditing() << -1, 0.5, 2, 3.5;

	ASSERT_EQ(weightsExpected[0].getEigenValue(), weights[0].getEigenValue());
	ASSERT_EQ(weightsExpected[1].getEigenValue(), weights[1].getEigenValue());



	simpleGradientDescent.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	simpleGradientDescent.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	weightsExpected[0] = Matrix<>(3, 3);
	weightsExpected[0].getEigenValueForEditing() << -2.75, -0.5, 1.75,
		-3.5, -1.25, 1,
		-4.25, -2, 0.25;
	weightsExpected[1] = Matrix<>(1, 4);
	weightsExpected[1].getEigenValueForEditing() << -4, -1.75, 0.5, 2.75;

	ASSERT_EQ(weightsExpected[0].getEigenValue(), weights[0].getEigenValue());
	ASSERT_EQ(weightsExpected[1].getEigenValue(), weights[1].getEigenValue());
}


TEST_F(SimpleGradientDescentTest, adjustWeightsWithMomentumGPU)
{
	SimpleGradientDescentOptions options;
	options.momentum = 0.5;
	options.learningRate = 0.5;
	options.weightDecayFac = 0;

	SimpleGradientDescent simpleGradientDescent(options);

	simpleGradientDescent.setCalculatorType(CT_GPU);

	simpleGradientDescent.initializeAlgorithm(networkTopology);

	simpleGradientDescent.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	simpleGradientDescent.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	std::vector<Matrix<>> weightsExpected(2);
	weightsExpected[0] = Matrix<>(3, 3);
	weightsExpected[0].getEigenValueForEditing() << -0.5, 1, 2.5,
		1, 2.5, 4,
		2.5, 4, 5.5;
	weightsExpected[1] = Matrix<>(1, 4);
	weightsExpected[1].getEigenValueForEditing() << -1, 0.5, 2, 3.5;

	ASSERT_EQ(weightsExpected[0].getEigenValue(), weights[0].getEigenValue());
	ASSERT_EQ(weightsExpected[1].getEigenValue(), weights[1].getEigenValue());



	simpleGradientDescent.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	simpleGradientDescent.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	weightsExpected[0] = Matrix<>(3, 3);
	weightsExpected[0].getEigenValueForEditing() << -2.75, -0.5, 1.75,
		-3.5, -1.25, 1,
		-4.25, -2, 0.25;
	weightsExpected[1] = Matrix<>(1, 4);
	weightsExpected[1].getEigenValueForEditing() << -4, -1.75, 0.5, 2.75;

	ASSERT_EQ(weightsExpected[0].getEigenValue(), weights[0].getEigenValue());
	ASSERT_EQ(weightsExpected[1].getEigenValue(), weights[1].getEigenValue());
}