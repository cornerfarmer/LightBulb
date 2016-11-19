#include "gtest/gtest.h"
#include <Mocks/MockEvolutionWorld.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

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
	std::vector<MockIndividual*> mockIndividuals;
	MockIndividual mockIndividualClone;

	EXPECT_CALL(*evolutionWorld, getPopulationSize()).WillRepeatedly(testing::Return(10));

	testing::Sequence seq;
	for (int i = 0; i < 20; i++)
	{
		mockIndividuals.push_back(new MockIndividual());
		EXPECT_CALL(*evolutionWorld, addNewIndividual(false)).InSequence(seq).WillOnce(testing::Return(mockIndividuals.back()));
		EXPECT_CALL(*mockIndividuals.back(), clone(false)).WillOnce(testing::Return(&mockIndividualClone));
	}
	EXPECT_CALL(mockIndividualClone, setEvolutionSource(Creation)).Times(20);
	
	std::vector<AbstractIndividual*> notUsedIndividuals;

	constantCreationCommand->execute(*evolutionWorld, notUsedIndividuals);
}
