#include "gtest/gtest.h"
#include <Mocks/MockTestableEvolutionEnvironment.hpp>
#include <Mocks/MockIndividual.hpp>
#include <Mocks/MockTestableCoevolutionEnvironment.hpp>
#include <Mocks/MockCombiningStrategy.hpp>
#include <Mocks/MockHallOfFameAlgorithm.hpp>
#include <Mocks/MockCoevolutionFitnessFunction.hpp>

using namespace LightBulb;

class AbstractCoevolutionEnvironmentTest : public testing::Test {
public:
	MockTestableCoevolutionEnvironment* coevolutionEnvironment;
	MockCombiningStrategy* combiningStrategy;
	MockCoevolutionFitnessFunction* coevolutionFitnessFunction;
	std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToAddAlgorithm;
	std::shared_ptr<AbstractHallOfFameAlgorithm> hallOfFameToChallengeAlgorithm;
	
	void SetUp() {
		combiningStrategy = new MockCombiningStrategy();
		coevolutionFitnessFunction = new MockCoevolutionFitnessFunction();
		hallOfFameToAddAlgorithm.reset(new MockHallOfFameAlgorithm());
		hallOfFameToChallengeAlgorithm.reset(new MockHallOfFameAlgorithm());
		coevolutionEnvironment = new MockTestableCoevolutionEnvironment(true, combiningStrategy, coevolutionFitnessFunction, &hallOfFameToAddAlgorithm, &hallOfFameToChallengeAlgorithm);
	}

	virtual ~AbstractCoevolutionEnvironmentTest()
	{
		delete coevolutionEnvironment;
	}
};

TEST_F(AbstractCoevolutionEnvironmentTest, doSimulationStep)
{
	CombiningStrategyResults result;
	std::map<const AbstractIndividual*, double>* fitnessValues = new std::map<const AbstractIndividual*, double>();
	MockIndividual bestIndividual;
	std::vector<std::pair<double, AbstractIndividual*>> highscore;
	std::map<std::string, bool> disabledDataSets;
	LearningState learningState(disabledDataSets, 5);
	coevolutionEnvironment->setLearningState(learningState);
	highscore.push_back(std::make_pair(42, &bestIndividual));
	{
		testing::InSequence s;
		EXPECT_CALL(*combiningStrategy, execute(testing::Ref(*coevolutionEnvironment))).WillOnce(testing::ReturnRef(result));
		EXPECT_CALL(*static_cast<MockHallOfFameAlgorithm*>(hallOfFameToChallengeAlgorithm.get()), execute(testing::Ref(*coevolutionEnvironment), testing::Ref(result))).Times(1);
		EXPECT_CALL(*coevolutionFitnessFunction, execute(testing::Ref(result))).WillOnce(testing::Return(fitnessValues));
		EXPECT_CALL(*coevolutionEnvironment, getHighscoreList()).WillOnce(testing::ReturnRef(highscore));
		EXPECT_CALL(*coevolutionEnvironment, rateIndividual(testing::Ref(bestIndividual))).Times(1);
		EXPECT_CALL(*static_cast<MockHallOfFameAlgorithm*>(hallOfFameToAddAlgorithm.get()), addMember(&bestIndividual)).Times(1);
	}

	coevolutionEnvironment->doSimulationStep();
}
