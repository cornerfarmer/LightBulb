#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockIndividual.hpp>
#include <Learning/Evolution/PerfectIndividualFoundCondition.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>
#include <Mocks/MockCombiningStrategy.hpp>

using namespace LightBulb;

class PerfectIndividualFoundConditionTest : public testing::Test {
public:
	PerfectIndividualFoundCondition* perfectIndividualFoundCondition;
	MockCoevolutionWorld* world;
	const MockEvolutionLearningRule* learningRule;
	MockCombiningStrategy combiningStrategy;
	MockIndividual individual1, individual2, individual3;
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	CombiningStrategyResults results;

	void SetUp() {
		perfectIndividualFoundCondition = new PerfectIndividualFoundCondition(2);
		AbstractEvolutionLearningRuleOptions options;
		learningRule = new MockEvolutionLearningRule(options);
		world = new MockCoevolutionWorld();
		highscore.push_back(std::make_pair(0, static_cast<AbstractIndividual*>(nullptr)));

		EXPECT_CALL(*learningRule, getWorld()).WillRepeatedly(testing::ReturnRef(*world));
		EXPECT_CALL(*world, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(combiningStrategy));
		EXPECT_CALL(*world, isParasiteWorld()).WillRepeatedly(testing::Return(true));
		
		results[&individual1][&individual2][0] = true;
		results[&individual2][&individual1][0] = false;
		results[&individual1][&individual3][0] = false;
		results[&individual3][&individual1][0] = true;
		results[&individual2][&individual3][0] = true;
		results[&individual3][&individual2][0] = false;
		EXPECT_CALL(combiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(results));

	}

	virtual ~PerfectIndividualFoundConditionTest()
	{
		delete perfectIndividualFoundCondition;
	}
};

TEST_F(PerfectIndividualFoundConditionTest, evaluateWithEmptyHighscore)
{
	highscore.clear();
	EXPECT_EQ(false, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));
}


TEST_F(PerfectIndividualFoundConditionTest, evaluateNegative)
{
	EXPECT_EQ(false, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));
}

TEST_F(PerfectIndividualFoundConditionTest, evaluatePositive)
{
	results[&individual1][&individual3][0] = true;
	results[&individual3][&individual1][0] = false;

	EXPECT_EQ(false, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));
	EXPECT_EQ(true, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));
}


TEST_F(PerfectIndividualFoundConditionTest, evaluateWithReset)
{
	results[&individual1][&individual3][0] = true;
	results[&individual3][&individual1][0] = false;

	EXPECT_EQ(false, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));

	results[&individual1][&individual3][0] = false;
	results[&individual3][&individual1][0] = true;

	EXPECT_EQ(false, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));



	results[&individual1][&individual3][0] = true;
	results[&individual3][&individual1][0] = false;

	EXPECT_EQ(false, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));
	EXPECT_EQ(true, perfectIndividualFoundCondition->evaluate(highscore, *learningRule));
}
