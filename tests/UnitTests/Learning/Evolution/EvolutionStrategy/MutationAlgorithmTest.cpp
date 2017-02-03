#include "UnitTestsPrec.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>
#include "LightBulb/Random/StandardRandomGenerator.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/Random/ZigguratGenerator.hpp"

using namespace LightBulb;

class MutationAlgorithmTest : public testing::TestWithParam<bool> {
public:
	MutationAlgorithm* mutationAlgorithm;
	ZigguratGenerator zigguratGenerator;
	void SetUp() {
		mutationAlgorithm = new MutationAlgorithm(1.6);
		if (GetParam())
			mutationAlgorithm->setCalculatorType(CT_GPU);
		zigguratGenerator.setSeed(123456789);
		mutationAlgorithm->setZigguratGenerator(zigguratGenerator);
	}

	virtual ~MutationAlgorithmTest()
	{
		delete mutationAlgorithm;
	}
};

INSTANTIATE_TEST_CASE_P(MutationAlgorithmTestMultDev, MutationAlgorithmTest, testing::Bool());

TEST_P(MutationAlgorithmTest, execute)
{
	MockIndividual individual;

	Vector<> mutationStrength(5);
	mutationStrength.getEigenValueForEditing() << 2, -5, 0, 7500000, -1000000;
	EXPECT_CALL(individual, getMutationStrength()).WillRepeatedly(testing::ReturnRef(mutationStrength));

	MockNeuralNetwork neuralNetwork;
	EXPECT_CALL(individual, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork));
	MockNetworkTopology networkTopology;
	EXPECT_CALL(neuralNetwork, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology));
	std::vector<Matrix<>> weights;
	EXPECT_CALL(networkTopology, getAllWeights()).WillRepeatedly(testing::ReturnRef(weights));

	weights.push_back(Matrix<>(2,2));
	weights[0].getEigenValueForEditing()(0, 0) = 2;
	weights[0].getEigenValueForEditing()(0, 1) = 1;
	weights[0].getEigenValueForEditing()(1, 0) = -5;
	weights[0].getEigenValueForEditing()(1, 1) = 0.1;
	weights.push_back(Matrix<>(1, 1));
	weights[1].getEigenValueForEditing()(0, 0) = 10;

	mutationAlgorithm->execute(individual);

	EXPECT_NEAR(0.231262, mutationStrength.getEigenValue()[0], 0.00001);
	EXPECT_NEAR(-8.35703, mutationStrength.getEigenValue()[1], 0.00001);
	EXPECT_NEAR(0.000001f, mutationStrength.getEigenValue()[2], 0.00001);
	EXPECT_NEAR(50, mutationStrength.getEigenValue()[3], 0.00001);
	EXPECT_NEAR(-50, mutationStrength.getEigenValue()[4], 0.00001);

	EXPECT_NEAR(1.826609, weights[0].getEigenValue()(0, 0), 0.00001);
	EXPECT_NEAR(23.00891, weights[0].getEigenValue()(0, 1), 0.00001);
	EXPECT_NEAR(-5.00000, weights[0].getEigenValue()(1, 0), 0.00001);
	EXPECT_NEAR(-44.92901, weights[0].getEigenValue()(1, 1), 0.00001);
	EXPECT_NEAR(37.36058, weights[1].getEigenValue()(0, 0), 0.00001);
}
