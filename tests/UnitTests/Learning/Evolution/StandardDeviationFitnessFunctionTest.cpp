#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/StandardDeviationFitnessFunction.hpp>

using namespace LightBulb;

class StandardDeviationFitnessFunctionTest : public testing::Test {
public:
	StandardDeviationFitnessFunction* standardDeviationFitnessFunction;

	void SetUp() {
		
	}

	virtual ~StandardDeviationFitnessFunctionTest()
	{
		delete standardDeviationFitnessFunction;
	}
};

TEST_F(StandardDeviationFitnessFunctionTest, execute)
{
	standardDeviationFitnessFunction = new StandardDeviationFitnessFunction(1);

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(10, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(6, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(2, static_cast<AbstractIndividual*>(nullptr)));

	standardDeviationFitnessFunction->execute(highscore);
	EXPECT_NEAR(7.26599, highscore[0].first, 0.00001);
	EXPECT_NEAR(3.26599, highscore[1].first, 0.00001);
	EXPECT_NEAR(-0.734014, highscore[2].first, 0.00001);

}


TEST_F(StandardDeviationFitnessFunctionTest, executeFails)
{
	standardDeviationFitnessFunction = new StandardDeviationFitnessFunction(5);

	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(10, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(6, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(2, static_cast<AbstractIndividual*>(nullptr)));

	EXPECT_THROW(standardDeviationFitnessFunction->execute(highscore), std::logic_error);
}
