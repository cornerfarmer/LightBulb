#include "gtest/gtest.h"
#include <Learning/Evolution/RoundRobinCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>

using namespace LightBulb;

class RoundRobinCombiningStrategyTest : public testing::Test {
public:
	RoundRobinCombiningStrategy* roundRobinCombiningStrategy;
	MockCoevolutionWorld world;
	MockEvolutionObject object1, object2, object3, object4, object5, object6;

	void SetUp()
	{
		roundRobinCombiningStrategy = new RoundRobinCombiningStrategy();
	}

	virtual ~RoundRobinCombiningStrategyTest()
	{
		delete roundRobinCombiningStrategy;
	}
};

TEST_F(RoundRobinCombiningStrategyTest, executeEmptyWorld)
{
	std::vector<AbstractEvolutionObject*> objects;
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	
	auto& result = roundRobinCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}

TEST_F(RoundRobinCombiningStrategyTest, executeSingleWorld)
{
	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	EXPECT_CALL(world, compareObjects(testing::_, testing::_, 0)).Times(6).WillRepeatedly(testing::Return(1));

	auto& result = roundRobinCombiningStrategy->execute(world);
	
	EXPECT_EQ(3, result.size());
	EXPECT_EQ(2, result[&object1].size());
	EXPECT_EQ(2, result[&object2].size());
	EXPECT_EQ(2, result[&object3].size());
}

TEST_F(RoundRobinCombiningStrategyTest, executeTwoWorlds)
{
	MockCoevolutionWorld parasiteWorld;
	roundRobinCombiningStrategy->setSecondWorld(parasiteWorld);

	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	std::vector<AbstractEvolutionObject*> parasiteObjects({ &object4 , &object5, &object6 });

	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(parasiteObjects));
	EXPECT_CALL(world, compareObjects(testing::_, testing::_, 0)).Times(9).WillRepeatedly(testing::Return(1));

	auto& result = roundRobinCombiningStrategy->execute(world);

	EXPECT_EQ(6, result.size());
	EXPECT_EQ(3, result[&object1].size());
	EXPECT_EQ(3, result[&object2].size());
	EXPECT_EQ(3, result[&object3].size());
	EXPECT_EQ(3, result[&object4].size());
	EXPECT_EQ(3, result[&object5].size());
	EXPECT_EQ(3, result[&object6].size());

}
