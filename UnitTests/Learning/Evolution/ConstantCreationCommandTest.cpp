#include "gtest/gtest.h"
#include <Mocks/MockEvolutionWorld.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Mocks/MockEvolutionObject.hpp>

class ConstantCreationCommandTest : public testing::Test {
public:
	ConstantCreationCommand* constantCreationCommand;

	void SetUp() {
		constantCreationCommand = new ConstantCreationCommand(30);
	}

	virtual ~ConstantCreationCommandTest()
	{
		delete constantCreationCommand;
	}
};

TEST_F(ConstantCreationCommandTest, executeReuseSelection)
{
	MockEvolutionWorld* evolutionWorld = new MockEvolutionWorld();
	std::vector<MockEvolutionObject*> mockEvolutionObjects;
	MockEvolutionObject mockEvolutionObjectClone;

	EXPECT_CALL(*evolutionWorld, getPopulationSize()).WillRepeatedly(testing::Return(10));

	testing::Sequence seq;
	for (int i = 0; i < 20; i++)
	{
		mockEvolutionObjects.push_back(new MockEvolutionObject());
		EXPECT_CALL(*evolutionWorld, addNewObject(false)).InSequence(seq).WillOnce(testing::Return(mockEvolutionObjects.back()));
		EXPECT_CALL(*mockEvolutionObjects.back(), clone(false)).WillOnce(testing::Return(&mockEvolutionObjectClone));
	}
	EXPECT_CALL(mockEvolutionObjectClone, setEvolutionSource(Creation)).Times(20);
	
	std::vector<AbstractEvolutionObject*> notUsedObjects;

	constantCreationCommand->execute(*evolutionWorld, &notUsedObjects);
}
