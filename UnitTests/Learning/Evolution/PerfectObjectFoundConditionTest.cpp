#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/PerfectObjectFoundCondition.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>
#include <Mocks/MockCombiningStrategy.hpp>

using namespace LightBulb;

class PerfectObjectFoundConditionTest : public testing::Test {
public:
	PerfectObjectFoundCondition* perfectObjectFoundCondition;
	MockCoevolutionWorld* world;
	const MockEvolutionLearningRule* learningRule;
	MockCombiningStrategy combiningStrategy;
	MockEvolutionObject object1, object2, object3;
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	CombiningStrategyResults results;

	void SetUp() {
		perfectObjectFoundCondition = new PerfectObjectFoundCondition(2);
		AbstractEvolutionLearningRuleOptions options;
		learningRule = new MockEvolutionLearningRule(options);
		world = new MockCoevolutionWorld();
		highscore.push_back(std::make_pair(0, static_cast<AbstractEvolutionObject*>(nullptr)));

		EXPECT_CALL(*learningRule, getWorld()).WillRepeatedly(testing::ReturnRef(*world));
		EXPECT_CALL(*world, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(combiningStrategy));
		EXPECT_CALL(*world, isParasiteWorld()).WillRepeatedly(testing::Return(true));
		
		results[&object1][&object2][0] = true;
		results[&object2][&object1][0] = false;
		results[&object1][&object3][0] = false;
		results[&object3][&object1][0] = true;
		results[&object2][&object3][0] = true;
		results[&object3][&object2][0] = false;
		EXPECT_CALL(combiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(results));

	}

	virtual ~PerfectObjectFoundConditionTest()
	{
		delete perfectObjectFoundCondition;
	}
};

TEST_F(PerfectObjectFoundConditionTest, evaluateWithEmptyHighscore)
{
	highscore.clear();
	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(highscore, *learningRule));
}


TEST_F(PerfectObjectFoundConditionTest, evaluateNegative)
{
	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(highscore, *learningRule));
}

TEST_F(PerfectObjectFoundConditionTest, evaluatePositive)
{
	results[&object1][&object3][0] = true;
	results[&object3][&object1][0] = false;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(highscore, *learningRule));
	EXPECT_EQ(true, perfectObjectFoundCondition->evaluate(highscore, *learningRule));
}


TEST_F(PerfectObjectFoundConditionTest, evaluateWithReset)
{
	results[&object1][&object3][0] = true;
	results[&object3][&object1][0] = false;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(highscore, *learningRule));

	results[&object1][&object3][0] = false;
	results[&object3][&object1][0] = true;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(highscore, *learningRule));



	results[&object1][&object3][0] = true;
	results[&object3][&object1][0] = false;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(highscore, *learningRule));
	EXPECT_EQ(true, perfectObjectFoundCondition->evaluate(highscore, *learningRule));
}
