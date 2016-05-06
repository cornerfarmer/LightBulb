#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Function/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>

using testing::Expectation;

class BipartiteEvolutionLearningRuleTest : public testing::Test {
public:
	BipartiteEvolutionLearningRule* bipartiteEvolutionLearningRule;
	MockEvolutionLearningRule* learningRule1;
	MockEvolutionLearningRule* learningRule2;

	void SetUp() {
		BipartiteEvolutionLearningRuleOptions options;
		AbstractEvolutionLearningRuleOptions subOptions;
		learningRule1 = new MockEvolutionLearningRule(subOptions);
		learningRule2 = new MockEvolutionLearningRule(subOptions);
		options.learningRule1 = learningRule1;
		options.learningRule2 = learningRule2;
		bipartiteEvolutionLearningRule = new BipartiteEvolutionLearningRule(options);
	}

	virtual ~BipartiteEvolutionLearningRuleTest()
	{
		delete bipartiteEvolutionLearningRule;
		delete learningRule1;
		delete learningRule2;
	}
};

TEST_F(BipartiteEvolutionLearningRuleTest, start)
{
	testing::InSequence s;

	EXPECT_CALL(*learningRule1, initializeTry()).Times(1);
	EXPECT_CALL(*learningRule2, initializeTry()).Times(1);

	EXPECT_CALL(*learningRule1, doIteration()).WillOnce(testing::Return(true));
	EXPECT_CALL(*learningRule2, doIteration()).WillOnce(testing::Return(false));

	EXPECT_CALL(*learningRule1, doIteration()).WillOnce(testing::Return(false));

	EXPECT_EQ(true, bipartiteEvolutionLearningRule->start());
}
