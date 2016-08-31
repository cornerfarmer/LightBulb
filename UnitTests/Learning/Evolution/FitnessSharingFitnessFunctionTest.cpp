#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/FitnessSharingFitnessFunction.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>

class FitnessSharingFitnessFunctionTest : public testing::Test {
public:
	FitnessSharingFitnessFunction* fitnessSharingFitnessFunction;

	void SetUp() {
		
	}

	virtual ~FitnessSharingFitnessFunctionTest()
	{
		delete fitnessSharingFitnessFunction;
	}
};

TEST_F(FitnessSharingFitnessFunctionTest, execute)
{
	fitnessSharingFitnessFunction = new FitnessSharingFitnessFunction(10, 2);

	MockEvolutionObject evolutionObject1, evolutionObject2;

	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(1, &evolutionObject1));
	highscore.push_back(std::make_pair(3, &evolutionObject2));

	MockNeuralNetwork neuralNetwork1, neuralNetwork2;

	EXPECT_CALL(evolutionObject1, getNeuralNetwork()).WillRepeatedly(testing::Return(&neuralNetwork1));
	EXPECT_CALL(evolutionObject2, getNeuralNetwork()).WillRepeatedly(testing::Return(&neuralNetwork2));

	MockNetworkTopology networkTopology1, networkTopology2;

	EXPECT_CALL(neuralNetwork1, getNetworkTopology()).WillRepeatedly(testing::Return(&networkTopology1));
	EXPECT_CALL(neuralNetwork2, getNetworkTopology()).WillRepeatedly(testing::Return(&networkTopology2));

	EXPECT_CALL(networkTopology1, calculateEuclideanDistance(testing::Ref(networkTopology2))).WillRepeatedly(testing::Return(2));
	EXPECT_CALL(networkTopology2, calculateEuclideanDistance(testing::Ref(networkTopology1))).WillRepeatedly(testing::Return(2));

	fitnessSharingFitnessFunction->execute(&highscore);

	EXPECT_EQ(0.625, highscore[0].first);
	EXPECT_EQ(1.875, highscore[1].first);

}
