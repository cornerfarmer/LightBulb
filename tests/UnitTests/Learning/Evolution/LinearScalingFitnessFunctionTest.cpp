#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <Learning/Evolution/LinearScalingFitnessFunction.hpp>

using namespace LightBulb;

class LinearScalingFitnessFunctionTest : public testing::Test {
public:
	LinearScalingFitnessFunction* linearScalingFitnessFunction;

	void SetUp() {
		
	}

	virtual ~LinearScalingFitnessFunctionTest()
	{
		delete linearScalingFitnessFunction;
	}
};

TEST_F(LinearScalingFitnessFunctionTest, execute)
{
	linearScalingFitnessFunction = new LinearScalingFitnessFunction(2, 5, false);

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(4, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(-3, static_cast<AbstractIndividual*>(nullptr)));

	linearScalingFitnessFunction->execute(highscore);
	EXPECT_EQ(13, highscore[0].first);
	EXPECT_EQ(-1, highscore[1].first);
}

TEST_F(LinearScalingFitnessFunctionTest, executeDynamic)
{
	linearScalingFitnessFunction = new LinearScalingFitnessFunction(2, 5, true);

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(4, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(-3, static_cast<AbstractIndividual*>(nullptr)));

	linearScalingFitnessFunction->execute(highscore);
	EXPECT_EQ(11, highscore[0].first);
	EXPECT_EQ(-3, highscore[1].first);
}
