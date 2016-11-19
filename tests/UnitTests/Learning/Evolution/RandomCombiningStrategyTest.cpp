#include "gtest/gtest.h"
#include <Learning/Evolution/RandomCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

class RandomCombiningStrategyTest : public testing::Test {
public:
	RandomCombiningStrategy* randomCombiningStrategy;
	MockCoevolutionWorld world;
	MockIndividual individual1, individual2, individual3, individual4, individual5, individual6;

	void SetUp()
	{
		EXPECT_CALL(world, getRoundCount()).WillRepeatedly(testing::Return(1));
	}

	virtual ~RandomCombiningStrategyTest()
	{
		delete randomCombiningStrategy;
	}
};

TEST_F(RandomCombiningStrategyTest, executeEmptyWorld)
{
	randomCombiningStrategy = new RandomCombiningStrategy(3);

	std::vector<AbstractIndividual*> individuals;
	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	auto& result = randomCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}

TEST_F(RandomCombiningStrategyTest, executeSingleWorld)
{
	srand(1);
	randomCombiningStrategy = new RandomCombiningStrategy(3);

	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(world, compareIndividuals(testing::_, testing::_, 0)).Times(9).WillRepeatedly(testing::Return(1));

	auto& result = randomCombiningStrategy->execute(world);
	
	EXPECT_EQ(3, result.size());
	EXPECT_EQ(3, result[&individual1].size());
	EXPECT_EQ(3, result[&individual2].size());
	EXPECT_EQ(3, result[&individual3].size());
}

TEST_F(RandomCombiningStrategyTest, executeTwoWorlds)
{
	randomCombiningStrategy = new RandomCombiningStrategy(2);
	
	MockCoevolutionWorld parasiteWorld;
	randomCombiningStrategy->setSecondWorld(parasiteWorld);

	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	std::vector<AbstractIndividual*> parasiteIndividuals({ &individual4 , &individual5, &individual6 });

	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(parasiteWorld, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));
	EXPECT_CALL(world, compareIndividuals(testing::_, testing::_, 0)).Times(6).WillRepeatedly(testing::Return(1));

	auto& result = randomCombiningStrategy->execute(world);

	EXPECT_EQ(5, result.size());
	EXPECT_EQ(2, result[&individual1].size());
	EXPECT_EQ(2, result[&individual2].size());
	EXPECT_EQ(2, result[&individual3].size());
	EXPECT_EQ(6, result[&individual4].size() + result[&individual5].size() + result[&individual6].size());
}
