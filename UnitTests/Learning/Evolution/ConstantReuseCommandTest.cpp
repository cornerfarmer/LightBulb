#include "gtest/gtest.h"
#include "Learning/Evolution/ConstantReuseCommand.hpp"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockReuseSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>

using namespace LightBulb;

class ConstantReuseCommandTest : public testing::Test {
public:
	ConstantReuseCommand* constantReuseCommand;
	MockReuseSelector* reuseSelector;

	std::map<AbstractEvolutionObject*, int> counter;
	std::vector<AbstractEvolutionObject*> selectedObjects;
	std::vector<AbstractEvolutionObject*> newObjectVector;
	std::vector<AbstractEvolutionObject*> notUsedObjects;
	void SetUp() {
		reuseSelector = new MockReuseSelector();
		
	}

	void SetUpExecute()
	{
		MockEvolutionObject selectedObject;

		selectedObjects.resize(1);
		selectedObjects[0] = new MockEvolutionObject();
		
		EXPECT_CALL(*reuseSelector, getReuseSelection()).WillRepeatedly(testing::ReturnRef(selectedObjects));
	}

	virtual ~ConstantReuseCommandTest()
	{
		delete constantReuseCommand;
		for (int i = 0; i < selectedObjects.size(); i++)
			delete(selectedObjects[i]);
	}
};

TEST_F(ConstantReuseCommandTest, selectStaticCount)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	std::map<AbstractEvolutionObject*, int> counter;
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);

	EXPECT_CALL(*reuseSelector, executeReuseSelection(10, highscore, counter)).Times(1);

	constantReuseCommand->select(highscore, counter);
}

TEST_F(ConstantReuseCommandTest, selectPercentage)
{
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore(10);
	std::map<AbstractEvolutionObject*, int> counter;
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 0.5);

	EXPECT_CALL(*reuseSelector, executeReuseSelection(5, highscore, counter)).Times(1);

	constantReuseCommand->select(highscore, counter);
}

TEST_F(ConstantReuseCommandTest, executeWithNoMultipleUsedObject)
{
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);
	SetUpExecute();
	counter[selectedObjects[0]] = 1;

	constantReuseCommand->execute(newObjectVector, counter, notUsedObjects);

	EXPECT_EQ(1, newObjectVector.size());
	EXPECT_EQ(selectedObjects[0], newObjectVector[0]);
	EXPECT_EQ(0, counter[selectedObjects[0]]);
}

TEST_F(ConstantReuseCommandTest, executeWithMultipleUsedObject)
{
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);
	SetUpExecute();
	counter[selectedObjects[0]] = 2;
	MockEvolutionObject clonedObject;

	EXPECT_CALL(*static_cast<MockEvolutionObject*>(selectedObjects[0]), clone(true)).Times(1).WillOnce(testing::Return(&clonedObject));

	constantReuseCommand->execute(newObjectVector, counter, notUsedObjects);

	EXPECT_EQ(1, newObjectVector.size());
	EXPECT_EQ(&clonedObject, newObjectVector[0]);
	EXPECT_EQ(1, counter[selectedObjects[0]]);
}

TEST_F(ConstantReuseCommandTest, executeWithTwoMultipleUsedObjectsAndANotUsedObject)
{
	constantReuseCommand = new ConstantReuseCommand(reuseSelector, 10);
	SetUpExecute();
	counter[selectedObjects[0]] = 2;
	MockEvolutionObject unusedObject;
	notUsedObjects.push_back(&unusedObject);

	EXPECT_CALL(unusedObject, copyPropertiesFrom(testing::Ref(*selectedObjects[0]))).Times(1);
	
	constantReuseCommand->execute(newObjectVector, counter, notUsedObjects);

	EXPECT_EQ(1, newObjectVector.size());
	EXPECT_EQ(&unusedObject, newObjectVector[0]);
	EXPECT_EQ(1, counter[selectedObjects[0]]);
}