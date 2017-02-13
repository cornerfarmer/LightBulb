#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"
#include "Mocks/MockNetworkTopology.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"

using namespace LightBulb;



class RMSPropLearningRateTest : public testing::TestWithParam<bool> {
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

INSTANTIATE_TEST_CASE_P(RMSPropLearningRateMultDev, RMSPropLearningRateTest, testing::Bool());

TEST_P(RMSPropLearningRateTest, adjustWeights)
{
	RMSPropLearningRateOptions options;

	RMSPropLearningRate rmsPropLearningRate(options);

	if (GetParam())
		rmsPropLearningRate.setCalculatorType(CT_GPU);

	rmsPropLearningRate.initializeAlgorithm(networkTopology);

	rmsPropLearningRate.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	rmsPropLearningRate.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	std::vector<Matrix<>> weightsExpected(2);
	weightsExpected[0] = Matrix<>(3, 3);
	weightsExpected[0].getEigenValueForEditing() << -0.133893490, 0.881966114, 1.95742786,
		2.85626054, 3.85772085, 4.86039448,
		5.85440922, 6.85480309, 7.85537767;
	weightsExpected[1] = Matrix<>(1, 4);
	weightsExpected[1].getEigenValueForEditing() << -0.139605761, 0.866106510, 1.88196611, 2.95742798;

	ASSERT_TRUE((weights[0].getEigenValue() - weightsExpected[0].getEigenValue()).norm() < 1e-3);
	ASSERT_TRUE((weights[1].getEigenValue() - weightsExpected[1].getEigenValue()).norm() < 1e-3);
	
	rmsPropLearningRate.adjustWeights(networkTopology, weights[0], 1, gradients[0]);
	rmsPropLearningRate.adjustWeights(networkTopology, weights[1], 2, gradients[1]);

	weightsExpected[0].getEigenValueForEditing() << -1.99190617, -0.955321074, 0.220491767,
		0.985442400, 1.98879886, 2.99494672,
		3.98118830, 4.98209381, 5.98341370;
	weightsExpected[1].getEigenValueForEditing() << -2.00505352, -0.991906166, 0.0446789265, 1.22049189;

	ASSERT_TRUE((weights[0].getEigenValue() - weightsExpected[0].getEigenValue()).norm() < 1e-3);
	ASSERT_TRUE((weights[1].getEigenValue() - weightsExpected[1].getEigenValue()).norm() < 1e-3);
}

