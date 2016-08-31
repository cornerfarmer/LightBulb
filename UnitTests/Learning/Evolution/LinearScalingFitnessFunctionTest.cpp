#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/LinearScalingFitnessFunction.hpp>

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

	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(4, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(-3, (AbstractEvolutionObject*)NULL));

	linearScalingFitnessFunction->execute(&highscore);
	EXPECT_EQ(13, highscore[0].first);
	EXPECT_EQ(-1, highscore[1].first);
}

TEST_F(LinearScalingFitnessFunctionTest, executeDynmaic)
{
	linearScalingFitnessFunction = new LinearScalingFitnessFunction(2, 5, true);

	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(4, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(-3, (AbstractEvolutionObject*)NULL));

	linearScalingFitnessFunction->execute(&highscore);
	EXPECT_EQ(5, highscore[0].first);
	EXPECT_EQ(-9, highscore[1].first);
}
