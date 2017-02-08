#include <LightBulb/Learning/Evolution/RandomCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionEnvironment.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp>
#include <LightBulb/Logging/AbstractLogger.hpp>

using namespace LightBulb;

class RandomCombiningStrategyTest : public testing::Test {
public:
	RandomCombiningStrategy* randomCombiningStrategy;
	MockCoevolutionEnvironment environment;
	MockIndividual individual1, individual2, individual3, individual4, individual5, individual6;

	void SetUp()
	{
		EXPECT_CALL(environment, getRoundCount()).WillRepeatedly(testing::Return(1));
	}

	virtual ~RandomCombiningStrategyTest()
	{
		delete randomCombiningStrategy;
	}
};

TEST_F(RandomCombiningStrategyTest, executeEmptyEnvironment)
{
	randomCombiningStrategy = new RandomCombiningStrategy(3);

	std::vector<AbstractIndividual*> individuals;
	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	auto& result = randomCombiningStrategy->execute(environment);

	//EXPECT_EQ(0, result.size());
}

TEST_F(RandomCombiningStrategyTest, executeSingleEnvironment)
{
	srand(1);
	randomCombiningStrategy = new RandomCombiningStrategy(3);

	//std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	//EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	//EXPECT_CALL(environment, compareIndividuals(testing::_, testing::_, 0)).Times(9).WillRepeatedly(testing::Return(1));

	//auto& result = randomCombiningStrategy->execute(environment);
	//
	//EXPECT_EQ(3, result.size());
	//EXPECT_EQ(3, result[&individual1].size());
	//EXPECT_EQ(3, result[&individual2].size());
	//EXPECT_EQ(3, result[&individual3].size());
}

TEST_F(RandomCombiningStrategyTest, executeTwoEnvironments)
{
	randomCombiningStrategy = new RandomCombiningStrategy(2);
	
	MockCoevolutionEnvironment parasiteEnvironment;
	randomCombiningStrategy->setSecondEnvironment(parasiteEnvironment);

	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3 });
	std::vector<AbstractIndividual*> parasiteIndividuals({ &individual4 , &individual5, &individual6 });

	//EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	//EXPECT_CALL(parasiteEnvironment, getIndividuals()).WillRepeatedly(testing::ReturnRef(parasiteIndividuals));
	//EXPECT_CALL(environment, compareIndividuals(testing::_, testing::_, 0)).Times(6).WillRepeatedly(testing::Return(1));

	//auto& result = randomCombiningStrategy->execute(environment);

	//EXPECT_EQ(5, result.size());
	//EXPECT_EQ(2, result[&individual1].size());
	//EXPECT_EQ(2, result[&individual2].size());
	//EXPECT_EQ(2, result[&individual3].size());
	//EXPECT_EQ(6, result[&individual4].size() + result[&individual5].size() + result[&individual6].size());
}
