#include "gtest/gtest.h"
#include <LightBulb/Learning/Evolution/SharedSamplingCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionEnvironment.hpp>
#include <Mocks/MockIndividual.hpp>
#include <Mocks/MockCombiningStrategy.hpp>

using namespace LightBulb;

class SharedSamplingCombiningStrategyTest : public testing::Test {
public:
	SharedSamplingCombiningStrategy* sharedSamplingCombiningStrategy;

	MockCoevolutionEnvironment environment;
	MockIndividual individual1, individual2, individual3, individual4, individual5, individual6;

	void SetUp()
	{
		EXPECT_CALL(environment, getRoundCount()).WillRepeatedly(testing::Return(1));
		sharedSamplingCombiningStrategy = new SharedSamplingCombiningStrategy(2);
	}

	virtual ~SharedSamplingCombiningStrategyTest()
	{
		delete sharedSamplingCombiningStrategy;
	}
};

TEST_F(SharedSamplingCombiningStrategyTest, executeTwoEmptyEnvironments)
{
	std::vector<AbstractIndividual*> individuals;
	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	MockCoevolutionEnvironment parasiteEnvironment;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteEnvironment, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondEnvironment(parasiteEnvironment);

	CombiningStrategyResults prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractIndividual*> parasiteIndividuals;
	EXPECT_CALL(parasiteEnvironment, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));

	auto& result = sharedSamplingCombiningStrategy->execute(environment);

	EXPECT_EQ(0, result.size());
}

TEST_F(SharedSamplingCombiningStrategyTest, executeEmptyParasiteEnvironment)
{
	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));

	MockCoevolutionEnvironment parasiteEnvironment;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteEnvironment, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondEnvironment(parasiteEnvironment);

	CombiningStrategyResults prevResults;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractIndividual*> parasiteIndividuals;
	EXPECT_CALL(parasiteEnvironment, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));

	auto& result = sharedSamplingCombiningStrategy->execute(environment);

	EXPECT_EQ(0, result.size());
}


TEST_F(SharedSamplingCombiningStrategyTest, executeSingleEnvironment)
{
	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	EXPECT_THROW(sharedSamplingCombiningStrategy->execute(environment), std::invalid_argument);
}

TEST_F(SharedSamplingCombiningStrategyTest, executeTwoEnvironments)
{
	MockCoevolutionEnvironment parasiteEnvironment;
	MockCombiningStrategy otherCombiningStrategy;
	EXPECT_CALL(parasiteEnvironment, getCombiningStrategy()).WillRepeatedly(testing::ReturnRef(otherCombiningStrategy));
	sharedSamplingCombiningStrategy->setSecondEnvironment(parasiteEnvironment);

	CombiningStrategyResults prevResults;
	prevResults[&individual4][&individual1][0] = true;
	prevResults[&individual4][&individual2][0] = true;
	prevResults[&individual5][&individual1][0] = true;
	prevResults[&individual6][&individual3][0] = true;
	EXPECT_CALL(otherCombiningStrategy, getPrevResults()).WillRepeatedly(testing::ReturnRef(prevResults));

	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	std::vector<AbstractIndividual*> parasiteIndividuals({ &individual4 , &individual5, &individual6 });

	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(parasiteEnvironment, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));

	{
		testing::InSequence s;
		EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual1), testing::Ref(individual4), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual1), testing::Ref(individual6), 0)).WillOnce(testing::Return(-1));
		EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual2), testing::Ref(individual4), 0)).WillOnce(testing::Return(-1));
		EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual2), testing::Ref(individual6), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual3), testing::Ref(individual4), 0)).WillOnce(testing::Return(1));
		EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual3), testing::Ref(individual6), 0)).WillOnce(testing::Return(1));
	}
	
	auto& result = sharedSamplingCombiningStrategy->execute(environment);

	EXPECT_EQ(5, result.size());
	EXPECT_EQ(2, result[&individual1].size());
	EXPECT_EQ(2, result[&individual2].size());
	EXPECT_EQ(2, result[&individual3].size());
	EXPECT_EQ(3, result[&individual4].size());
	EXPECT_EQ(3, result[&individual6].size());

}
