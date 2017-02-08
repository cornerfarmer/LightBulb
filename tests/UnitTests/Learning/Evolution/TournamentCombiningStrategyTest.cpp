#include <LightBulb/Learning/Evolution/TournamentCombiningStrategy.hpp>
#include <Mocks/MockCoevolutionEnvironment.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp>

using namespace LightBulb;

class TournamentCombiningStrategyTest : public testing::Test {
public:
	TournamentCombiningStrategy* tournamentCombiningStrategy;
	MockCoevolutionEnvironment environment;
	MockIndividual individual1, individual2, individual3, individual4, individual5, individual6;

	void SetUp()
	{
		tournamentCombiningStrategy = new TournamentCombiningStrategy();
	}

	virtual ~TournamentCombiningStrategyTest()
	{
		delete tournamentCombiningStrategy;
	}
};

TEST_F(TournamentCombiningStrategyTest, executeEmptyEnvironment)
{
	std::vector<AbstractIndividual*> individuals;
	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	
	auto result = tournamentCombiningStrategy->execute(environment);

	//EXPECT_EQ(0, result.size());
}

TEST_F(TournamentCombiningStrategyTest, executeSingleEnvironment)
{
	tournamentCombiningStrategy = new TournamentCombiningStrategy(false);

	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2, &individual3, &individual4, &individual5, &individual6 });
	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	//EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual1), testing::Ref(individual2), 0)).WillOnce(testing::Return(1));
	//EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual3), testing::Ref(individual4), 0)).WillOnce(testing::Return(-1));
	//EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual5), testing::Ref(individual6), 0)).WillOnce(testing::Return(1));

	//EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual1), testing::Ref(individual4), 0)).WillOnce(testing::Return(1));

	//EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual1), testing::Ref(individual5), 0)).WillOnce(testing::Return(-1));

	//auto& result = tournamentCombiningStrategy->execute(environment);
	//
	//EXPECT_EQ(6, result.size());
	//EXPECT_EQ(3, result[&individual1].size());
	//EXPECT_EQ(1, result[&individual2].size());
	//EXPECT_EQ(1, result[&individual3].size());
	//EXPECT_EQ(2, result[&individual4].size());
	//EXPECT_EQ(2, result[&individual5].size());
	//EXPECT_EQ(1, result[&individual6].size());
}

TEST_F(TournamentCombiningStrategyTest, executeTwoEnvironments)
{
	EXPECT_EQ("false", "Implemented");
}
