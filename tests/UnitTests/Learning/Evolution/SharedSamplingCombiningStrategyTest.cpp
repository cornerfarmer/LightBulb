#include "gtest/gtest.h"
#include <Learning/Evolution/SharedSamplingCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionWorld.hpp>
#include <Mocks/MockIndividual.hpp>
#include <Mocks/MockCombiningStrategy.hpp>

using namespace LightBulb;

class SharedSamplingCombiningStrategyTest : public testing::Test {
public:
	SharedSamplingCombiningStrategy* sharedSamplingCombiningStrategy;

	MockCoevolutionWorld world;
	MockIndividual individual1, individual2, individual3, individual4, individual5, individual6;

	void SetUp()
	{
		EXPECT_CALL(world, getRoundCount()).WillRepeatedly(testing::Return(1));
		sharedSamplingCombiningStrategy = new SharedSamplingCombiningStrategy(2);
	}

	virtual ~SharedSamplingCombiningStrategyTest()
	{
		delete sharedSamplingCombiningStrategy;
	}
};

TEST_F(SharedSamplingCombiningStrategyTest, executeTwoEmptyWorlds)
{
	std::vector<AbstractIndividual*> individuals;
	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(parasiteWorld);

	CombiningStrategyResults prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractIndividual*> parasiteIndividuals;
	EXPECT_CALL(parasiteWorld, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));

	auto& result = sharedSamplingCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}

TEST_F(SharedSamplingCombiningStrategyTest, executeEmptyParasiteWorld)
{
	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));

	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(parasiteWorld);

	CombiningStrategyResults prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractIndividual*> parasiteIndividuals;
	EXPECT_CALL(parasiteWorld, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));

	auto& result = sharedSamplingCombiningStrategy->execute(world);

	EXPECT_EQ(0, result.size());
}


TEST_F(SharedSamplingCombiningStrategyTest, executeSingleWorld)
{
	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	EXPECT_THROW(sharedSamplingCombiningStrategy->execute(world), std::invalid_argument);
}

TEST_F(SharedSamplingCombiningStrategyTest, executeTwoWorlds)
{
	MockCoevolutionWorld parasiteWorld;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteWorld, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondWorld(parasiteWorld);

	CombiningStrategyResults prevResults;
	prevResults[&individual4][&individual1][0] = true;
	prevResults[&individual4][&individual2][0] = true;
	prevResults[&individual5][&individual1][0] = true;
	prevResults[&individual6][&individual3][0] = true;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	std::vector<AbstractIndividual*> parasiteIndividuals({ &individual4 , &individual5, &individual6 });

	EXPECT_CALL(world, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(parasiteWorld, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));

	{
		testing::InSequence s;
		EXPECT_CALL(world, compareIndividuals(testing::Ref(individual1), testing::Ref(individual4), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareIndividuals(testing::Ref(individual1), testing::Ref(individual6), 0)).WillOnce(testing::Return(-1));
		EXPECT_CALL(world, compareIndividuals(testing::Ref(individual2), testing::Ref(individual4), 0)).WillOnce(testing::Return(-1));
		EXPECT_CALL(world, compareIndividuals(testing::Ref(individual2), testing::Ref(individual6), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareIndividuals(testing::Ref(individual3), testing::Ref(individual4), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(world, compareIndividuals(testing::Ref(individual3), testing::Ref(individual6), 0)).WillOnce(testing::Return(1));
	}
	
	auto& result = sharedSamplingCombiningStrategy->execute(world);

	EXPECT_EQ(5, result.size());
	EXPECT_EQ(2, result[&individual1].size());
	EXPECT_EQ(2, result[&individual2].size());
	EXPECT_EQ(2, result[&individual3].size());
	EXPECT_EQ(3, result[&individual4].size());
	EXPECT_EQ(3, result[&individual6].size());

}
