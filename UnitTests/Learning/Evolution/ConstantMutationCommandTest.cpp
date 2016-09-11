#include "gtest/gtest.h"
#include "Learning/Evolution/ConstantMutationCommand.hpp"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockmutationAlgorithm.hpp>
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>

using namespace LightBulb;

class ConstantMutationCommandTest : public testing::Test {
public:
	ConstantMutationCommand* constantMutationCommand;
	MockMutationAlgorithm* mutationAlgorithm;
	MockMutationSelector* mutationSelector;

	std::map<AbstractEvolutionObject*, int> counter;
	std::vector<AbstractEvolutionObject*> selectedObjects;
	std::vector<AbstractEvolutionObject*> newObjectVector;
	std::vector<AbstractEvolutionObject*> notUsedObjects;
	void SetUp() {
		mutationAlgorithm = new MockMutationAlgorithm();
		mutationSelector = new MockMutationSelector();
		constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, mutationSelector, 10);
	}

	void SetUpExecute()
	{
		MockEvolutionObject selectedObject;

		selectedObjects.resize(1);
		selectedObjects[0] = new MockEvolutionObject();
		
		EXPECT_CALL(*mutationSelector, getMutationSelection()).WillRepeatedly(testing::Return(&selectedObjects));
	}

	virtual ~ConstantMutationCommandTest()
	{
		delete constantMutationCommand;
		for (int i = 0; i < selectedObjects.size(); i++)
			delete(selectedObjects[i]);
	}
};

TEST_F(ConstantMutationCommandTest, selectStaticCount)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	std::map<AbstractEvolutionObject*, int> counter;
	constantMutationCommand->setMutationCount(10);

	EXPECT_CALL(*mutationSelector, executeMutationSelection(10, &highscore, &counter)).Times(1);

	constantMutationCommand->select(&highscore, &counter);
}

TEST_F(ConstantMutationCommandTest, selectPercentage)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore(10);
	std::map<AbstractEvolutionObject*, int> counter;
	constantMutationCommand->setMutationPercentage(0.5);

	EXPECT_CALL(*mutationSelector, executeMutationSelection(5, &highscore, &counter)).Times(1);

	constantMutationCommand->select(&highscore, &counter);
}

TEST_F(ConstantMutationCommandTest, executeWithNoMultipleUsedObject)
{
	SetUpExecute();
	counter[selectedObjects[0]] = 1;

	EXPECT_CALL(*mutationAlgorithm, execute(selectedObjects[0])).Times(1);

	constantMutationCommand->execute(&newObjectVector, &counter, &notUsedObjects);

	EXPECT_EQ(1, newObjectVector.size());
	EXPECT_EQ(selectedObjects[0], newObjectVector[0]);
	EXPECT_EQ(0, counter[selectedObjects[0]]);
}

TEST_F(ConstantMutationCommandTest, executeWithMultipleUsedObject)
{
	SetUpExecute();
	counter[selectedObjects[0]] = 2;
	MockEvolutionObject clonedObject;

	EXPECT_CALL(*(MockEvolutionObject*)selectedObjects[0], clone(true)).Times(1).WillOnce(testing::Return(&clonedObject));
	EXPECT_CALL(*mutationAlgorithm, execute(&clonedObject)).Times(1);

	constantMutationCommand->execute(&newObjectVector, &counter, &notUsedObjects);

	EXPECT_EQ(1, newObjectVector.size());
	EXPECT_EQ(&clonedObject, newObjectVector[0]);
	EXPECT_EQ(1, counter[selectedObjects[0]]);
}

TEST_F(ConstantMutationCommandTest, executeWithTwoMultipleUsedObjectsAndANotUsedObject)
{
	SetUpExecute();
	counter[selectedObjects[0]] = 2;
	MockEvolutionObject unusedObject;
	notUsedObjects.push_back(&unusedObject);

	EXPECT_CALL(*mutationAlgorithm, execute(&unusedObject)).Times(1);

	EXPECT_CALL(unusedObject, copyPropertiesFrom(selectedObjects[0])).Times(1);

	constantMutationCommand->execute(&newObjectVector, &counter, &notUsedObjects);

	EXPECT_EQ(1, newObjectVector.size());
	EXPECT_EQ(&unusedObject, newObjectVector[0]);
	EXPECT_EQ(1, counter[selectedObjects[0]]);
}