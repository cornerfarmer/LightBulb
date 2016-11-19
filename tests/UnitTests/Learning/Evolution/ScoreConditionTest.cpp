#include "gtest/gtest.h"
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Learning/Evolution/ScoreCondition.hpp>
#include "Mocks/MockEvolutionLearningRule.hpp"

using namespace LightBulb;

class ScoreConditionTest : public testing::Test {
public:
	ScoreCondition* scoreCondition;
	MockEvolutionLearningRule* evolutionLearningRule;
	void SetUp() {
		scoreCondition = new ScoreCondition(50);
		AbstractEvolutionLearningRuleOptions options;
		evolutionLearningRule = new MockEvolutionLearningRule(options);
	}

	virtual ~ScoreConditionTest()
	{
		delete scoreCondition;
	}
};

TEST_F(ScoreConditionTest, evaluateWithEmptyHighscore)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	EXPECT_EQ(false, scoreCondition->evaluate(highscore, *evolutionLearningRule));
}


TEST_F(ScoreConditionTest, evaluatePositive)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(100, static_cast<AbstractIndividual*>(nullptr)));
	highscore.push_back(std::make_pair(42, static_cast<AbstractIndividual*>(nullptr)));
	EXPECT_EQ(true, scoreCondition->evaluate(highscore, *evolutionLearningRule));
}


TEST_F(ScoreConditionTest, evaluateNegative)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	highscore.push_back(std::make_pair(42, static_cast<AbstractIndividual*>(nullptr)));
	EXPECT_EQ(false, scoreCondition->evaluate(highscore, *evolutionLearningRule));
}