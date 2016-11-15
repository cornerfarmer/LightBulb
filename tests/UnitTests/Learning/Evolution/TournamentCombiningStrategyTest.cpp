#include "gtest/gtest.h"
#include <Learning/Evolution/TournamentCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>

using namespace LightBulb;

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
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	
	auto result = tournamentCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}

TEST_F(TournamentCombiningStrategyTest, executeSingleWorld)
{
	tournamentCombiningStrategy = new TournamentCombiningStrategy(false);

	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3, &object4, &object5, &object6 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	EXPECT_CALL(world, compareObjects(testing::Ref(object1), testing::Ref(object2), 0)).WillOnce(testing::Return(1));
	EXPECT_CALL(world, compareObjects(testing::Ref(object3), testing::Ref(object4), 0)).WillOnce(testing::Return(-1));
	EXPECT_CALL(world, compareObjects(testing::Ref(object5), testing::Ref(object6), 0)).WillOnce(testing::Return(1));

	EXPECT_CALL(world, compareObjects(testing::Ref(object1), testing::Ref(object4), 0)).WillOnce(testing::Return(1));

	EXPECT_CALL(world, compareObjects(testing::Ref(object1), testing::Ref(object5), 0)).WillOnce(testing::Return(-1));

	auto& result = tournamentCombiningStrategy->execute(world);
	
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
