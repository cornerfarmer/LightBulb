#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/PositiveMakerFitnessFunction.hpp>

class PositiveMakerFitnessFunctionTest : public testing::Test {
public:
	PositiveMakerFitnessFunction* positiveMakerFitnessFunction;

	void SetUp() {
		
	}

	virtual ~PositiveMakerFitnessFunctionTest()
	{
		delete positiveMakerFitnessFunction;
	}
};

TEST_F(PositiveMakerFitnessFunctionTest, execute)
{
	positiveMakerFitnessFunction = new PositiveMakerFitnessFunction(10);

	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(4, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(-3, (AbstractEvolutionObject*)NULL));
	highscore.push_back(std::make_pair(-13, (AbstractEvolutionObject*)NULL));

	positiveMakerFitnessFunction->execute(&highscore);
	EXPECT_EQ(14, highscore[0].first);
	EXPECT_EQ(7, highscore[1].first);
	EXPECT_EQ(0, highscore[2].first);

}
