#include "UnitTestsPrec.hpp"
#include <Mocks/MockCoevolutionEnvironment.hpp>
#include <LightBulb/Learning/Evolution/FitnessCondition.hpp>
#include "Mocks/MockEvolutionLearningRule.hpp"

using namespace LightBulb;

class FitnessConditionTest : public testing::Test {
public:
	FitnessCondition* fitnessCondition;
	MockEvolutionLearningRule* evolutionLearningRule;
	void SetUp() {
		fitnessCondition = new FitnessCondition(50);
		AbstractEvolutionLearningRuleOptions options;
		evolutionLearningRule = new MockEvolutionLearningRule(options);
	}

	virtual ~FitnessConditionTest()
	{
		delete fitnessCondition;
	}
};

TEST_F(FitnessConditionTest, evaluateWithEmptyHighscore)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	EXPECT_EQ(false, fitnessCondition->evaluate(highscore, *evolutionLearningRule));
}


TEST_F(FitnessConditionTest, evaluatePositive)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(100, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(42, static_cast<AbstractIndividual*>(nullptr)));
	EXPECT_EQ(true, fitnessCondition->evaluate(highscore, *evolutionLearningRule));
}


TEST_F(FitnessConditionTest, evaluateNegative)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(42, static_cast<AbstractIndividual*>(nullptr)));
	EXPECT_EQ(false, fitnessCondition->evaluate(highscore, *evolutionLearningRule));
}