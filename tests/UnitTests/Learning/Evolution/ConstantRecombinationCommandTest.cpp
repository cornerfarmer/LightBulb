#include "gtest/gtest.h"
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockRecombinationAlgorithm.hpp>
#include <Mocks/MockRecombinationSelector.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

class ConstantRecombinationCommandTest : public testing::Test {
public:
	ConstantRecombinationCommand* constantRecombinationCommand;
	MockRecombinationAlgorithm* recombinationAlgorithm;
	MockRecombinationSelector* recombinationSelector;

	std::map<AbstractIndividual*, int> counter;
	std::vector<AbstractIndividual*> selectedIndividuals;
	std::vector<AbstractIndividual*> newIndividualVector;
	std::vector<AbstractIndividual*> notUsedIndividuals;
	void SetUp() {
		recombinationAlgorithm = new MockRecombinationAlgorithm();
		recombinationSelector = new MockRecombinationSelector();
		
	}

	void SetUpExecute()
	{
		MockIndividual firstSelectedIndividual, secondSelectedIndividual;

		selectedIndividuals.resize(2);
		selectedIndividuals[0] = new MockIndividual();
		selectedIndividuals[1] = new MockIndividual();

		EXPECT_CALL(*recombinationSelector, getRecombinationSelection()).WillRepeatedly(testing::ReturnRef(selectedIndividuals));
	}

	virtual ~ConstantRecombinationCommandTest()
	{
		delete constantRecombinationCommand;
		for (int i = 0; i < selectedIndividuals.size(); i++)
			delete(selectedIndividuals[i]);
	}
};

TEST_F(ConstantRecombinationCommandTest, selectStaticCount)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	std::map<AbstractIndividual*, int> counter;
	constantRecombinationCommand = new ConstantRecombinationCommand(recombinationAlgorithm, recombinationSelector, 10);

	EXPECT_CALL(*recombinationSelector, executeRecombinationSelection(10, highscore, counter)).Times(1);

	constantRecombinationCommand->select(highscore, counter);
}

TEST_F(ConstantRecombinationCommandTest, selectPercentage)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore(10);
	std::map<AbstractIndividual*, int> counter;
	constantRecombinationCommand = new ConstantRecombinationCommand(recombinationAlgorithm, recombinationSelector, 0.5);

	EXPECT_CALL(*recombinationSelector, executeRecombinationSelection(5, highscore, counter)).Times(1);

	constantRecombinationCommand->select(highscore, counter);
}

TEST_F(ConstantRecombinationCommandTest, executeWithNoMultipleUsedIndividuals)
{
	constantRecombinationCommand = new ConstantRecombinationCommand(recombinationAlgorithm, recombinationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 1;
	counter[selectedIndividuals[1]] = 1;

	EXPECT_CALL(*recombinationAlgorithm, execute(testing::Ref(*selectedIndividuals[0]), testing::Ref(*selectedIndividuals[1]))).Times(1);

	constantRecombinationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(selectedIndividuals[0], newIndividualVector[0]);
	EXPECT_EQ(0, counter[selectedIndividuals[0]]);
	EXPECT_EQ(0, counter[selectedIndividuals[1]]);
}

TEST_F(ConstantRecombinationCommandTest, executeWithOneMultipleUsedIndividual1)
{
	constantRecombinationCommand = new ConstantRecombinationCommand(recombinationAlgorithm, recombinationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 2;
	counter[selectedIndividuals[1]] = 1;

	EXPECT_CALL(*recombinationAlgorithm, execute(testing::Ref(*selectedIndividuals[1]), testing::Ref(*selectedIndividuals[0]))).Times(1);

	constantRecombinationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(selectedIndividuals[1], newIndividualVector[0]);
	EXPECT_EQ(1, counter[selectedIndividuals[0]]);
	EXPECT_EQ(0, counter[selectedIndividuals[1]]);
}


TEST_F(ConstantRecombinationCommandTest, executeWithOneMultipleUsedIndividual2)
{
	constantRecombinationCommand = new ConstantRecombinationCommand(recombinationAlgorithm, recombinationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 1;
	counter[selectedIndividuals[1]] = 2;

	EXPECT_CALL(*recombinationAlgorithm, execute(testing::Ref(*selectedIndividuals[0]), testing::Ref(*selectedIndividuals[1]))).Times(1);

	constantRecombinationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(selectedIndividuals[0], newIndividualVector[0]);
	EXPECT_EQ(0, counter[selectedIndividuals[0]]);
	EXPECT_EQ(1, counter[selectedIndividuals[1]]);
}


TEST_F(ConstantRecombinationCommandTest, executeWithTwoMultipleUsedIndividuals)
{
	constantRecombinationCommand = new ConstantRecombinationCommand(recombinationAlgorithm, recombinationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 2;
	counter[selectedIndividuals[1]] = 2;
	MockIndividual clonedIndividual;

	EXPECT_CALL(*static_cast<MockIndividual*>(selectedIndividuals[1]), clone(true)).Times(1).WillOnce(testing::Return(&clonedIndividual));
	EXPECT_CALL(*recombinationAlgorithm, execute(testing::Ref(clonedIndividual), testing::Ref(*selectedIndividuals[0]))).Times(1);

	constantRecombinationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(&clonedIndividual newIndividualVector[0]);
	EXPECT_EQ(1, counter[selectedIndividuals[0]]);
	EXPECT_EQ(1, counter[selectedIndividuals[1]]);
}

TEST_F(ConstantRecombinationCommandTest, executeWithTwoMultipleUsedIndividualsAndANotUsedIndividual)
{
	constantRecombinationCommand = new ConstantRecombinationCommand(recombinationAlgorithm, recombinationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 2;
	counter[selectedIndividuals[1]] = 2;
	MockIndividual unusedIndividual;
	notUsedIndividuals.push_back(&unusedIndividual);

	EXPECT_CALL(*recombinationAlgorithm, execute(testing::Ref(unusedIndividual), testing::Ref(*selectedIndividuals[0]))).Times(1);

	EXPECT_CALL(unusedIndividual, copyPropertiesFrom(testing::Ref(*selectedIndividuals[1]))).Times(1);

	constantRecombinationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(&unusedIndividual, newIndividualVector[0]);
	EXPECT_EQ(1, counter[selectedIndividuals[0]]);
	EXPECT_EQ(1, counter[selectedIndividuals[1]]);
}