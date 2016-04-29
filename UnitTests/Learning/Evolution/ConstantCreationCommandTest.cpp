#include "gtest/gtest.h"
#include <Mocks/MockEvolutionWorld.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>

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

	EXPECT_CALL(*evolutionWorld, getPopulationSize()).WillRepeatedly(testing::Return(10));
	EXPECT_CALL(*evolutionWorld, addNewObject(true)).Times(20);

	constantCreationCommand->execute(*evolutionWorld);
}
