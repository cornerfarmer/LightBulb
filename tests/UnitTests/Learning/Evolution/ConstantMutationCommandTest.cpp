#include "LightBulb/Learning/Evolution/ConstantMutationCommand.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationAlgorithm.hpp>
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

class ConstantMutationCommandTest : public testing::Test {
public:
	ConstantMutationCommand* constantMutationCommand;
	MockMutationAlgorithm* mutationAlgorithm;
	MockMutationSelector* mutationSelector;

	std::map<AbstractIndividual*, int> counter;
	std::vector<AbstractIndividual*> selectedIndividuals;
	std::vector<AbstractIndividual*> newIndividualVector;
	std::vector<AbstractIndividual*> notUsedIndividuals;
	void SetUp() {
		mutationAlgorithm = new MockMutationAlgorithm();
		mutationSelector = new MockMutationSelector();
		
	}

	void SetUpExecute()
	{
		MockIndividual selectedIndividual;

		selectedIndividuals.resize(1);
		selectedIndividuals[0] = new MockIndividual();
		
		EXPECT_CALL(*mutationSelector, getMutationSelection()).WillRepeatedly(testing::ReturnRef(selectedIndividuals));
	}

	virtual ~ConstantMutationCommandTest()
	{
		delete constantMutationCommand;
		for (int i = 0; i < selectedIndividuals.size(); i++)
			delete(selectedIndividuals[i]);
	}
};

TEST_F(ConstantMutationCommandTest, selectStaticCount)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	std::map<AbstractIndividual*, int> counter;
	constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, mutationSelector, 10);

	EXPECT_CALL(*mutationSelector, executeMutationSelection(10, highscore, counter)).Times(1);

	constantMutationCommand->select(highscore, counter);
}

TEST_F(ConstantMutationCommandTest, selectPercentage)
{
	std::vector<std::pair<double, AbstractIndividual*>> highscore(10);
	std::map<AbstractIndividual*, int> counter;
	constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, mutationSelector, 0.5);

	EXPECT_CALL(*mutationSelector, executeMutationSelection(5, highscore, counter)).Times(1);

	constantMutationCommand->select(highscore, counter);
}

TEST_F(ConstantMutationCommandTest, executeWithNoMultipleUsedObject)
{
	constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, mutationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 1;

	EXPECT_CALL(*mutationAlgorithm, execute(testing::Ref(*selectedIndividuals[0]))).Times(1);

	constantMutationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(selectedIndividuals[0], newIndividualVector[0]);
	EXPECT_EQ(0, counter[selectedIndividuals[0]]);
}

TEST_F(ConstantMutationCommandTest, executeWithMultipleUsedIndividuals)
{
	constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, mutationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 2;
	MockIndividual clonedIndividual;

	EXPECT_CALL(*static_cast<MockIndividual*>(selectedIndividuals[0]), clone(true)).Times(1).WillOnce(testing::Return(&clonedIndividual));
	EXPECT_CALL(*mutationAlgorithm, execute(testing::Ref(clonedIndividual))).Times(1);

	constantMutationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(&clonedIndividual, newIndividualVector[0]);
	EXPECT_EQ(1, counter[selectedIndividuals[0]]);
}

TEST_F(ConstantMutationCommandTest, executeWithTwoMultipleUsedIndividualsAndANotUsedIndividual)
{
	constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, mutationSelector, 10);
	SetUpExecute();
	counter[selectedIndividuals[0]] = 2;
	MockIndividual unusedIndividual;
	notUsedIndividuals.push_back(&unusedIndividual);

	EXPECT_CALL(*mutationAlgorithm, execute(testing::Ref(unusedIndividual))).Times(1);

	EXPECT_CALL(unusedIndividual, copyPropertiesFrom(testing::Ref(*selectedIndividuals[0]))).Times(1);

	constantMutationCommand->execute(newIndividualVector, counter, notUsedIndividuals);

	EXPECT_EQ(1, newIndividualVector.size());
	EXPECT_EQ(&unusedIndividual, newIndividualVector[0]);
	EXPECT_EQ(1, counter[selectedIndividuals[0]]);
}
