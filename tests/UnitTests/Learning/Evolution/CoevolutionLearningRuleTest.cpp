#include <Mocks/MockMutationSelector.hpp>
#include <LightBulb/Learning/Evolution/CoevolutionLearningRule.hpp>
#include <Mocks/MockEvolutionLearningRule.hpp>
#include <Mocks/MockLearningResult.hpp>
#include "Mocks/MockLogger.hpp"

using testing::Expectation;
using namespace LightBulb;

class CoevolutionLearningRuleTest : public testing::Test {
public:
	CoevolutionLearningRule* coevolutionLearningRule;
	MockEvolutionLearningRule* learningRule1;
	MockEvolutionLearningRule* learningRule2;
	MockLogger logger;

	void SetUp() {
		CoevolutionLearningRuleOptions options;
		options.logger = &logger;
		AbstractEvolutionLearningRuleOptions subOptions;
		learningRule1 = new MockEvolutionLearningRule(subOptions);
		learningRule2 = new MockEvolutionLearningRule(subOptions);
		options.learningRule1 = learningRule1;
		options.learningRule2 = learningRule2;
		coevolutionLearningRule = new CoevolutionLearningRule(options);
	}

	virtual ~CoevolutionLearningRuleTest()
	{
		delete coevolutionLearningRule;
		delete learningRule1;
		delete learningRule2;
	}
};

TEST_F(CoevolutionLearningRuleTest, start)
{
	testing::InSequence s;

	EXPECT_CALL(*learningRule1, initializeTry()).Times(1);
	EXPECT_CALL(*learningRule2, initializeTry()).Times(1);

	EXPECT_CALL(*learningRule1, doIteration());
	EXPECT_CALL(*learningRule2, doIteration());
	EXPECT_CALL(*learningRule2, hasLearningSucceeded()).WillOnce(testing::Return(true));

	MockLearningResult learningResult;

	EXPECT_CALL(*learningRule1, getLearningResult()).WillOnce(testing::Return(&learningResult));
	
	EXPECT_EQ(&learningResult, coevolutionLearningRule->start());
}
