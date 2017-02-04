#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/ExponentialFitnessFunction.hpp>

using namespace LightBulb;

class ExponentialFitnessFunctionTest : public testing::Test {
public:
	ExponentialFitnessFunction* exponentialFitnessFunction;

	void SetUp() {
		
	}

	virtual ~ExponentialFitnessFunctionTest()
	{
		delete exponentialFitnessFunction;
	}
};

TEST_F(ExponentialFitnessFunctionTest, execute)
{
	exponentialFitnessFunction = new ExponentialFitnessFunction(2, 5, 3);

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(4, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(-3, static_cast<AbstractIndividual*>(nullptr)));

	exponentialFitnessFunction->execute(highscore);
	EXPECT_EQ(529, highscore[0].first);
	EXPECT_EQ(144, highscore[1].first);

}
