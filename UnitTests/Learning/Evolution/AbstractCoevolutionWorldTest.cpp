#include "gtest/gtest.h"
#include <Mocks/MockTestableEvolutionWorld.hpp>
#include <Mocks/MockEvolutionObject.hpp>
#include <Mocks/MockTestableCoevolutionWorld.hpp>
#include <Mocks/MockCombiningStrategy.hpp>
#include <Mocks/MockHallOfFameAlgorithm.hpp>
#include <Mocks/MockCoevolutionFitnessFunction.hpp>

class AbstractCoevolutionWorldTest : public testing::Test {
public:
	MockTestableCoevolutionWorld* coevolutionWorld;
	MockCombiningStrategy* combiningStrategy;
	MockCoevolutionFitnessFunction* coevolutionFitnessFunction;
	MockHallOfFameAlgorithm* hallOfFameToAddAlgorithm;
	MockHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm;
	void SetUp() {
		combiningStrategy = new MockCombiningStrategy();
		coevolutionFitnessFunction = new MockCoevolutionFitnessFunction();
		hallOfFameToAddAlgorithm = new MockHallOfFameAlgorithm();
		hallOfFameToChallengeAlgorithm = new MockHallOfFameAlgorithm();
		coevolutionWorld = new MockTestableCoevolutionWorld(true, combiningStrategy, coevolutionFitnessFunction, hallOfFameToAddAlgorithm, hallOfFameToChallengeAlgorithm);
	}

	virtual ~AbstractCoevolutionWorldTest()
	{
		delete coevolutionWorld;
	}
};

TEST_F(AbstractCoevolutionWorldTest, doSimulationStep)
{
	std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, bool>> result;
	std::map<AbstractEvolutionObject*, double>* fitnessValues = new std::map<AbstractEvolutionObject*, double>();
	MockEvolutionObject bestObject;
	std::vector<std::pair<double, AbstractEvolutionObject*>> highscore;
	highscore.push_back(std::make_pair(42, &bestObject));
	{
		testing::InSequence s;
		EXPECT_CALL(*combiningStrategy, execute(coevolutionWorld)).WillOnce(testing::Return(&result));
		EXPECT_CALL(*hallOfFameToChallengeAlgorithm, execute(coevolutionWorld, testing::Ref(result))).Times(1);
		EXPECT_CALL(*coevolutionFitnessFunction, execute(testing::Ref(result))).WillOnce(testing::Return(fitnessValues));
		EXPECT_CALL(*coevolutionWorld, getHighscoreList()).WillOnce(testing::Return(&highscore));
		EXPECT_CALL(*coevolutionWorld, rateKI(&bestObject)).Times(1);
		EXPECT_CALL(*hallOfFameToChallengeAlgorithm, addMember(&bestObject)).Times(1);
	}

	coevolutionWorld->doSimulationStep();
}
