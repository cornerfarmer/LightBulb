#include "gtest/gtest.h"
#include "Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockmutationSelector.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Learning/Evolution/FullHallOfFameAlgorithm.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Learning/Evolution/RandomHallOfFameAlgorithm.hpp>

using namespace LightBulb;

class RandomHallOfFameAlgorithmTest : public testing::Test {
public:
	RandomHallOfFameAlgorithm* randomHallOfFameAlgorithm;

	void SetUp() {
		randomHallOfFameAlgorithm = new RandomHallOfFameAlgorithm(2);
	}

	virtual ~RandomHallOfFameAlgorithmTest()
	{
		delete randomHallOfFameAlgorithm;
	}
};

TEST_F(RandomHallOfFameAlgorithmTest, execute)
{
	MockCoevolutionWorld world;
	CombiningStrategyResults results;

	MockEvolutionObject hallOfFameMember1, hallOfFameMember2;
	MockEvolutionObject* hallOfFameMember1Clone = new MockEvolutionObject(), *hallOfFameMember2Clone = new MockEvolutionObject();
	EXPECT_CALL(hallOfFameMember1, clone(false)).WillRepeatedly(testing::Return(hallOfFameMember1Clone));
	EXPECT_CALL(hallOfFameMember2, clone(false)).WillRepeatedly(testing::Return(hallOfFameMember2Clone));
	randomHallOfFameAlgorithm->addMember(&hallOfFameMember1);
	randomHallOfFameAlgorithm->addMember(&hallOfFameMember2);

	MockEvolutionObject object1, object2;
	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));
	EXPECT_CALL(world, compareObjects(&object2, hallOfFameMember1Clone, 0)).WillOnce(testing::Return(1));
	EXPECT_CALL(world, compareObjects(&object1, hallOfFameMember1Clone, 0)).WillOnce(testing::Return(0));
	EXPECT_CALL(world, compareObjects(&object2, hallOfFameMember2Clone, 0)).WillOnce(testing::Return(1));
	EXPECT_CALL(world, compareObjects(&object1, hallOfFameMember2Clone, 0)).WillOnce(testing::Return(1));

	randomHallOfFameAlgorithm->execute(&world, results);

	EXPECT_EQ(false, results[&object1][hallOfFameMember1Clone][0]);
	EXPECT_EQ(true, results[hallOfFameMember1Clone][&object1][0]);
	EXPECT_EQ(true, results[&object2][hallOfFameMember1Clone][0]);
	EXPECT_EQ(false, results[hallOfFameMember1Clone][&object2][0]);

	EXPECT_EQ(true, results[&object1][hallOfFameMember2Clone][0]);
	EXPECT_EQ(false, results[hallOfFameMember2Clone][&object1][0]);
	EXPECT_EQ(true, results[&object2][hallOfFameMember2Clone][0]);
	EXPECT_EQ(false, results[hallOfFameMember2Clone][&object2][0]);

}
