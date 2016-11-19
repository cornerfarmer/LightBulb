#include "gtest/gtest.h"
#include "Learning/Evolution/ConstantReuseCommand.hpp"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockReuseSelector.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

class ConstantReuseCommandTest : public testing::Test {
public:
	ConstantReuseCommand* constantReuseCommand;
	MockReuseSelector* reuseSelector;

	std::map<AbstractIndividual*, int> counter;
	std::vector<AbstractIndividual*> selectedIndividuals;
	std::vector<AbstractIndividual*> newIndividualVector;
	std::vector<AbstractIndividual*> notUsedIndividuals;
	void SetUp() {
		reuseSelector = new MockReuseSelector();
		
	}

	void SetUpExecute()
	{
		MockIndividual selectedIndividual;

		selectedIndividuals.resize(1);
		selectedIndividuals[0] = new MockIndividual();
		
		EXPECT_CALL(*reuseSelector, getReuseSelection()).WillRepeatedly(testing::ReturnRef(selectedIndividuals));
	}

	virtual ~ConstantReuseCommandTest()
	{
		delete constantReuseCommand;
		for (int i = 0; i < selectedIndividuals.size(); i++)
			delete(selectedIndividuals[i]);
	}
};

TEST_F(ConstantReuseCommandTest, selectStaticCount)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	std::map<AbstractIndividual*, int> counter;
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);

	EXPECT_CALL(*reuseSelector, executeReuseSelection(10, highscore, counter)).Times(1);

	constantReuseCommand->select(highscore, counter);
}

TEST_F(ConstantReuseCommandTest, selectPercentage)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore(10);
	std::map<AbstractIndividual*, int> counter;
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 0.5);

	EXPECT_CALL(*reuseSelector, executeReuseSelection(5, highscore, counter)).Times(1);

	constantReuseCommand->select(highscore, counter);
}

TEST_F(ConstantReuseCommandTest, executeWithNoMultipleUsedIndividual)
{
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 1;

	constantReuseCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(selectedIndividuals[0], newIndividualVector[0]);
	EXPECT_EQ(0, counter[selectedIndividuals[0]]);
}

TEST_F(ConstantReuseCommandTest, executeWithMultipleUsedIndividuals)
{
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 2;
	MockIndividual clonedIndividual;

	EXPECT_CALL(*static_cast<MockIndividual*>(selectedIndividuals[0]), clone(true)).Times(1).WillOnce(testing::Return(&clonedIndividual));

	constantReuseCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(&clonedIndividual, newIndividualVector[0]);
	EXPECT_EQ(1, counter[selectedIndividuals[0]]);
}

TEST_F(ConstantReuseCommandTest, executeWithTwoMultipleUsedIndividualsAndANotUsedIndividual)
{
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 2;
	MockIndividual unusedIndividual;
	notUsedIndividuals.push_back(&unusedIndividual);

	EXPECT_CALL(unusedIndividual, copyPropertiesFrom(testing::Ref(*selectedIndividuals[0]))).Times(1);
	
	constantReuseCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(&unusedIndividual, newIndividualVector[0]);
	EXPECT_EQ(1, counter[selectedIndividuals[0]]);
}