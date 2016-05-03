#include "gtest/gtest.h"
#include <Learning/Evolution/TournamentCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>

class TournamentCombiningStrategyTest : public testing::Test {
public:
	TournamentCombiningStrategy* tournamentCombiningStrategy;
	MockCoevolutionWorld world;
	MockEvolutionObject object1, object2, object3, object4, object5, object6;

	void SetUp()
	{
		tournamentCombiningStrategy = new TournamentCombiningStrategy();
	}

	virtual ~TournamentCombiningStrategyTest()
	{
		delete tournamentCombiningStrategy;
	}
};

TEST_F(TournamentCombiningStrategyTest, executeEmptyWorld)
{
	std::vector<AbstractEvolutionObject*> objects;
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));
	
	auto result = tournamentCombiningStrategy->execute(&world);

	EXPECT_EQ(0, result.size());
}

TEST_F(TournamentCombiningStrategyTest, executeSingleWorld)
{
	tournamentCombiningStrategy->setDoShuffleBeforeTournament(false);

	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3, &object4, &object5, &object6 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));
	EXPECT_CALL(world, compareObjects(&object1, &object2)).WillOnce(testing::Return(1));
	EXPECT_CALL(world, compareObjects(&object3, &object4)).WillOnce(testing::Return(-1));
	EXPECT_CALL(world, compareObjects(&object5, &object6)).WillOnce(testing::Return(1));

	EXPECT_CALL(world, compareObjects(&object1, &object4)).WillOnce(testing::Return(1));

	EXPECT_CALL(world, compareObjects(&object1, &object5)).WillOnce(testing::Return(-1));

	auto result = tournamentCombiningStrategy->execute(&world);
	
	EXPECT_EQ(6, result.size());
	EXPECT_EQ(3, result[&object1].size());
	EXPECT_EQ(1, result[&object2].size());
	EXPECT_EQ(1, result[&object3].size());
	EXPECT_EQ(2, result[&object4].size());
	EXPECT_EQ(2, result[&object5].size());
	EXPECT_EQ(1, result[&object6].size());
}

TEST_F(TournamentCombiningStrategyTest, executeTwoWorlds)
{
	EXPECT_EQ("false", "Implemented");
}
