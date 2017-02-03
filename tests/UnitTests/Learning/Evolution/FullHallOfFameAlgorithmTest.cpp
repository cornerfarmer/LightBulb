#include "UnitTestsPrec.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include <Mocks/MockMutationSelector.hpp>
#include <Mocks/MockIndividual.hpp>
#include <LightBulb/Learning/Evolution/FullHallOfFameAlgorithm.hpp>
#include <Mocks/MockCoevolutionEnvironment.hpp>
#include <LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp>
#include <LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp>
#include <LightBulb/Logging/AbstractLogger.hpp>

using namespace LightBulb;

class FullHallOfFameAlgorithmTest : public testing::Test {
public:
	FullHallOfFameAlgorithm* fullHallOfFameAlgorithm;

	void SetUp() {
		fullHallOfFameAlgorithm = new FullHallOfFameAlgorithm();
	}

	virtual ~FullHallOfFameAlgorithmTest()
	{
		delete fullHallOfFameAlgorithm;
	}
};

TEST_F(FullHallOfFameAlgorithmTest, execute)
{
	MockCoevolutionEnvironment environment;
	CombiningStrategyResults results;

	MockIndividual hallOfFameMember1, hallOfFameMember2;
	MockIndividual* hallOfFameMember1Clone = new MockIndividual(), *hallOfFameMember2Clone = new MockIndividual();
	EXPECT_CALL(hallOfFameMember1, clone(false)).WillRepeatedly(testing::Return(hallOfFameMember1Clone));
	EXPECT_CALL(hallOfFameMember2, clone(false)).WillRepeatedly(testing::Return(hallOfFameMember2Clone));
	fullHallOfFameAlgorithm->addMember(&hallOfFameMember1);
	fullHallOfFameAlgorithm->addMember(&hallOfFameMember2);

	MockIndividual individual1, individual2;
	std::vector<AbstractIndividual*> individuals({ &individual1 , &individual2 });
	EXPECT_CALL(environment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(environment, getRoundCount()).WillRepeatedly(testing::Return(1));
	EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual2), testing::Ref(*hallOfFameMember1Clone), 0)).WillOnce(testing::Return(1));
	EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual1), testing::Ref(*hallOfFameMember1Clone), 0)).WillOnce(testing::Return(0));
	EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual2), testing::Ref(*hallOfFameMember2Clone), 0)).WillOnce(testing::Return(1));
	EXPECT_CALL(environment, compareIndividuals(testing::Ref(individual1), testing::Ref(*hallOfFameMember2Clone), 0)).WillOnce(testing::Return(1));

	fullHallOfFameAlgorithm->execute(environment, results);

	EXPECT_EQ(false, results[&individual1][hallOfFameMember1Clone][0]);
	EXPECT_EQ(true, results[hallOfFameMember1Clone][&individual1][0]);
	EXPECT_EQ(true, results[&individual2][hallOfFameMember1Clone][0]);
	EXPECT_EQ(false, results[hallOfFameMember1Clone][&individual2][0]);

	EXPECT_EQ(true, results[&individual1][hallOfFameMember2Clone][0]);
	EXPECT_EQ(false, results[hallOfFameMember2Clone][&individual1][0]);
	EXPECT_EQ(true, results[&individual2][hallOfFameMember2Clone][0]);
	EXPECT_EQ(false, results[hallOfFameMember2Clone][&individual2][0]);
}
