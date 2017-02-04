#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/FitnessSharingFitnessFunction.hpp>
#include <Mocks/MockNeuralNetwork.hpp>
#include <Mocks/MockNetworkTopology.hpp>

using namespace LightBulb;

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

	MockIndividual individual1, individual2;

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(1, &individual1));
	highscore.push_back(std::make_pair(3, &individual2));

	MockNeuralNetwork neuralNetwork1, neuralNetwork2;

	EXPECT_CALL(individual1, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork1));
	EXPECT_CALL(individual2, getNeuralNetwork()).WillRepeatedly(testing::ReturnRef(neuralNetwork2));

	MockNetworkTopology networkTopology1, networkTopology2;

	EXPECT_CALL(neuralNetwork1, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology1));
	EXPECT_CALL(neuralNetwork2, getNetworkTopology()).WillRepeatedly(testing::ReturnRef(networkTopology2));

	EXPECT_CALL(networkTopology1, calculateEuclideanDistance(testing::Ref(networkTopology2))).WillRepeatedly(testing::Return(2));
	EXPECT_CALL(networkTopology2, calculateEuclideanDistance(testing::Ref(networkTopology1))).WillRepeatedly(testing::Return(2));

	fitnessSharingFitnessFunction->execute(highscore);

	EXPECT_EQ(0.625, highscore[0].first);
	EXPECT_EQ(1.875, highscore[1].first);

}
