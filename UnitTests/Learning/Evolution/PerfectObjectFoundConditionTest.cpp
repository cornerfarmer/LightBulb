#include "gtest/gtest.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/PerfectObjectFoundCondition.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>
#include <Mocks/MockCombiningStrategy.hpp>

class PerfectObjectFoundConditionTest : public testing::Test {
public:
	PerfectObjectFoundCondition* perfectObjectFoundCondition;
	MockCoevolutionWorld world;
	MockEvolutionLearningRule* learningRule;
	MockCombiningStrategy combiningStrategy;
	MockEvolutionObject object1, object2, object3;
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> results;

	void SetUp() {
		perfectObjectFoundCondition = new PerfectObjectFoundCondition(2);
		AbstractEvolutionLearningRuleOptions options;
		learningRule = new MockEvolutionLearningRule(options);
		highscore.push_back(std::make_pair(0, (AbstractEvolutionObject*)NULL));

		EXPECT_CALL(*learningRule, getWorld()).WillRepeatedly(testing::Return(&world));
		EXPECT_CALL(world, getCombiningStrategy()).WillRepeatedly(testing::Return(&combiningStrategy));
		EXPECT_CALL(world, isParasiteWorld()).WillRepeatedly(testing::Return(true));
		
		results[&object1][&object2] = true;
		results[&object2][&object1] = false;
		results[&object1][&object3] = false;
		results[&object3][&object1] = true;
		results[&object2][&object3] = true;
		results[&object3][&object2] = false;
		EXPECT_CALL(combiningStrategy, getPrevResults()).WillRepeatedly(testing::Return(&results));

	}

	virtual ~PerfectObjectFoundConditionTest()
	{
		delete perfectObjectFoundCondition;
	}
};

TEST_F(PerfectObjectFoundConditionTest, evaluateWithEmptyHighscore)
{
	highscore.clear();
	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(&highscore, NULL));
}


TEST_F(PerfectObjectFoundConditionTest, evaluateNegative)
{
	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(&highscore, learningRule));
}

TEST_F(PerfectObjectFoundConditionTest, evaluatePositive)
{
	results[&object1][&object3] = true;
	results[&object3][&object1] = false;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(&highscore, learningRule));
	EXPECT_EQ(true, perfectObjectFoundCondition->evaluate(&highscore, learningRule));
}


TEST_F(PerfectObjectFoundConditionTest, evaluateWithReset)
{
	results[&object1][&object3] = true;
	results[&object3][&object1] = false;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(&highscore, learningRule));

	results[&object1][&object3] = false;
	results[&object3][&object1] = true;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(&highscore, learningRule));



	results[&object1][&object3] = true;
	results[&object3][&object1] = false;

	EXPECT_EQ(false, perfectObjectFoundCondition->evaluate(&highscore, learningRule));
	EXPECT_EQ(true, perfectObjectFoundCondition->evaluate(&highscore, learningRule));
}
