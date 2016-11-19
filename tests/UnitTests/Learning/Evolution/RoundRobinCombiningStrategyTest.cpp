#include "gtest/gtest.h"
#include <Learning/Evolution/RoundRobinCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

class RoundRobinCombiningStrategyTest : public testing::Test {
public:
	RoundRobinCombiningStrategy* roundRobinCombiningStrategy;
	MockCoevolutionWorld world;
	MockIndividual individual1, individual2, individual3, individual4, individual5, individual6;

	void SetUp()
	{
		EXPECT_CALL(world, getRoundCount()).WillRepeatedly(testing::Return(1));
		roundRobinCombiningStrategy = new RoundRobinCombiningStrategy();
	}

	virtual ~RoundRobinCombiningStrategyTest()
	{
		delete roundRobinCombiningStrategy;
	}
};

TEST_F(RoundRobinCombiningStrategyTest, executeEmptyWorld)
{
	std::vector<AbstractIndividual*> individuals;
	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	auto& result = roundRobinCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}

TEST_F(RoundRobinCombiningStrategyTest, executeSingleWorld)
{
	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(world, compareIndividuals(testing::_, testing::_, 0)).Times(6).WillRepeatedly(testing::Return(1));

	auto& result = roundRobinCombiningStrategy->execute(world);
	
	EXPECT_EQ(3, result.size());
	EXPECT_EQ(2, result[&individual1].size());
	EXPECT_EQ(2, result[&individual2].size());
	EXPECT_EQ(2, result[&individual3].size());
}

TEST_F(RoundRobinCombiningStrategyTest, executeTwoWorlds)
{
	MockCoevolutionWorld parasiteWorld;
	roundRobinCombiningStrategy->setSecondWorld(parasiteWorld);

	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	std::vector<AbstractIndividual*> parasiteIndividuals({ &individual4 , &individual5, &individual6 });

	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(parasiteWorld, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));
	EXPECT_CALL(world, compareIndividuals(testing::_, testing::_, 0)).Times(9).WillRepeatedly(testing::Return(1));

	auto& result = roundRobinCombiningStrategy->execute(world);

	EXPECT_EQ(6, result.size());
	EXPECT_EQ(3, result[&individual1].size());
	EXPECT_EQ(3, result[&individual2].size());
	EXPECT_EQ(3, result[&individual3].size());
	EXPECT_EQ(3, result[&individual4].size());
	EXPECT_EQ(3, result[&individual5].size());
	EXPECT_EQ(3, result[&individual6].size());

}
