#include "UnitTestsPrec.hpp"
#include <Mocks/MockEvolutionEnvironment.hpp>
#include <LightBulb/Learning/Evolution/ConstantCreationCommand.hpp>
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
	MockEvolutionEnvironment* evolutionEnvironment = new MockEvolutionEnvironment();
	std::vector<MockIndividual*> mockIndividuals;
	MockIndividual mockIndividualClone;

	EXPECT_CALL(*evolutionEnvironment, getPopulationSize()).WillRepeatedly(testing::Return(10));

	testing::Sequence seq;
	for (int i = 0; i < 20; i++)
	{
		mockIndividuals.push_back(new MockIndividual());
		EXPECT_CALL(*evolutionEnvironment, addNewIndividual(false)).InSequence(seq).WillOnce(testing::Return(mockIndividuals.back()));
		EXPECT_CALL(*mockIndividuals.back(), clone(false)).WillOnce(testing::Return(&mockIndividualClone));
	}
	EXPECT_CALL(mockIndividualClone, setEvolutionSource(Creation)).Times(20);
	
	std::vector<AbstractIndividual*> notUsedIndividuals;

	constantCreationCommand->execute(*evolutionEnvironment, notUsedIndividuals);
}
