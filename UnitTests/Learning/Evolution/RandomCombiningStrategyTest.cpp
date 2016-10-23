#include "gtest/gtest.h"
#include <Learning/Evolution/RandomCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>

using namespace LightBulb;

class RandomCombiningStrategyTest : public testing::Test {
public:
	RandomCombiningStrategy* randomCombiningStrategy;
	MockCoevolutionWorld world;
	MockEvolutionObject object1, object2, object3, object4, object5, object6;

	void SetUp()
	{
		
	}

	virtual ~RandomCombiningStrategyTest()
	{
		delete randomCombiningStrategy;
	}
};

TEST_F(RandomCombiningStrategyTest, executeEmptyWorld)
{
	randomCombiningStrategy = new RandomCombiningStrategy(3);

	std::vector<AbstractEvolutionObject*> objects;
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	
	auto& result = randomCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}

TEST_F(RandomCombiningStrategyTest, executeSingleWorld)
{
	srand(1);
	randomCombiningStrategy = new RandomCombiningStrategy(3);

	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	EXPECT_CALL(world, compareObjects(testing::_, testing::_, 0)).Times(9).WillRepeatedly(testing::Return(1));

	auto& result = randomCombiningStrategy->execute(world);
	
	EXPECT_EQ(3, result.size());
	EXPECT_EQ(3, result[&object1].size());
	EXPECT_EQ(3, result[&object2].size());
	EXPECT_EQ(3, result[&object3].size());
}

TEST_F(RandomCombiningStrategyTest, executeTwoWorlds)
{
	randomCombiningStrategy = new RandomCombiningStrategy(2);
	
	MockCoevolutionWorld parasiteWorld;
	randomCombiningStrategy->setSecondWorld(parasiteWorld);

	std::vector<AbstractEvolutionObject*> objects({ &object1 , &object2, &object3 });
	std::vector<AbstractEvolutionObject*> parasiteObjects({ &object4 , &object5, &object6 });

	EXPECT_CALL(world, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(objects));
	EXPECT_CALL(parasiteWorld, getEvolutionObjects()).WillRepeatedly(testing::ReturnRef(parasiteObjects));
	EXPECT_CALL(world, compareObjects(testing::_, testing::_, 0)).Times(6).WillRepeatedly(testing::Return(1));

	auto& result = randomCombiningStrategy->execute(world);

	EXPECT_EQ(5, result.size());
	EXPECT_EQ(2, result[&object1].size());
	EXPECT_EQ(2, result[&object2].size());
	EXPECT_EQ(2, result[&object3].size());
	EXPECT_EQ(6, result[&object4].size() + result[&object5].size() + result[&object6].size());
}
