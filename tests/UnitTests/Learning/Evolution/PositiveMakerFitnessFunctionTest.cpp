#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/PositiveMakerFitnessFunction.hpp>

using namespace LightBulb;

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

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(4, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(-3, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(-13, static_cast<AbstractIndividual*>(nullptr)));

	positiveMakerFitnessFunction->execute(highscore);
	EXPECT_EQ(14, highscore[0].first);
	EXPECT_EQ(7, highscore[1].first);
	EXPECT_EQ(0, highscore[2].first);

}
