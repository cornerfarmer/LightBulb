#include "gtest/gtest.h"
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Mocks/MockCreationCommand.hpp>
#include <Mocks/MockMutationCommand.hpp>
#include <Mocks/MockSelectionCommand.hpp>
#include <Mocks/MockExitCondition.hpp>
#include <Mocks/MockFitnessFunction.hpp>
#include <Mocks/MockRecombinationCommand.hpp>
#include <Mocks/MockReuseCommand.hpp>
#include <Mocks/MockEvolutionWorld.hpp>
#include <Mocks/MockLogger.hpp>
#include <Mocks/MockEvolutionObject.hpp>

class EvolutionLearningRuleTest : public testing::Test {
public:
	EvolutionLearningRule* evolutionLearningRule;
	MockCreationCommand* creationCommand;
	MockExitCondition* exitCondition;
	MockFitnessFunction* fitnessFunction;
	MockMutationCommand* mutationCommand;
	MockRecombinationCommand* recombinationCommand;
	MockReuseCommand* reuseCommand;
	MockSelectionCommand* selectionCommand;
	MockEvolutionWorld* evolutionWorld;
	MockLogger* logger;

	void SetUp()
	{
		creationCommand = new MockCreationCommand();
		exitCondition = new MockExitCondition();
		fitnessFunction = new MockFitnessFunction();
		mutationCommand = new MockMutationCommand();
		recombinationCommand = new MockRecombinationCommand();
		reuseCommand = new MockReuseCommand();
		selectionCommand = new MockSelectionCommand();
		evolutionWorld = new MockEvolutionWorld();
		logger = new MockLogger();
	}

	void createLearningRule() {

		EvolutionLearningRuleOptions options;

		options.creationCommands.push_back(creationCommand);
		options.exitConditions.push_back(exitCondition);
		options.fitnessFunctions.push_back(fitnessFunction);
		options.mutationsCommands.push_back(mutationCommand);
		options.recombinationCommands.push_back(recombinationCommand);
		options.reuseCommands.push_back(reuseCommand);
		options.selectionCommands.push_back(selectionCommand);
		options.world = evolutionWorld;
		options.logger = logger;
		options.scoreGoal = 50;

		evolutionLearningRule = new EvolutionLearningRule(options);
	}

	virtual ~EvolutionLearningRuleTest()
	{
		delete creationCommand;
		delete exitCondition;
		delete fitnessFunction;
		delete mutationCommand;
		delete recombinationCommand;
		delete reuseCommand;
		delete selectionCommand;
		delete evolutionWorld;
		delete logger;
		delete evolutionLearningRule;
	}
};

TEST_F(EvolutionLearningRuleTest, setLogger)
{
	EXPECT_CALL(*creationCommand, setLogger(logger));
	EXPECT_CALL(*exitCondition, setLogger(logger));
	EXPECT_CALL(*fitnessFunction, setLogger(logger));
	EXPECT_CALL(*mutationCommand, setLogger(logger));
	EXPECT_CALL(*recombinationCommand, setLogger(logger));
	EXPECT_CALL(*reuseCommand, setLogger(logger));
	EXPECT_CALL(*selectionCommand, setLogger(logger));

	createLearningRule();
}

TEST_F(EvolutionLearningRuleTest, learn)
{
	createLearningRule();

	std::vector<AbstractEvolutionObject*> objects;
	EXPECT_CALL(*evolutionWorld, getEvolutionObjects()).WillRepeatedly(testing::Return(&objects));
	EXPECT_CALL(*evolutionWorld, getPopulationSize()).WillRepeatedly(testing::Return(0));
	testing::Expectation lastIterationExpectation;
	{
		testing::InSequence s;

		// Initialize try
		EXPECT_CALL(*evolutionWorld, clearPopulation()).Times(1);
		EXPECT_CALL(*evolutionWorld, initializeForLearning()).Times(1);

		// iteration 0
		EXPECT_CALL(*evolutionWorld, reset()).Times(1);
		EXPECT_CALL(*creationCommand, execute(testing::Ref(*evolutionWorld))).Times(1);
		EXPECT_CALL(*evolutionWorld, doSimulationStep()).WillOnce(testing::Return(false));
		std::vector<std::pair<double, AbstractEvolutionObject*>> emptyHighscore;
		EXPECT_CALL(*evolutionWorld, getHighscoreList()).WillOnce(testing::Return(&emptyHighscore));

		EXPECT_CALL(*exitCondition, evaluate(&emptyHighscore, evolutionLearningRule)).WillOnce(testing::Return(false));
		EXPECT_CALL(*fitnessFunction, execute(&emptyHighscore)).Times(1);
		lastIterationExpectation = EXPECT_CALL(*selectionCommand, execute(&emptyHighscore, &objects, testing::_)).Times(1);
	}

	EXPECT_CALL(*evolutionWorld, getPopulationSize()).After(lastIterationExpectation).WillRepeatedly(testing::Return(1));
	std::vector<std::pair<double, AbstractEvolutionObject*>> fullHighscore;
	fullHighscore.push_back(std::make_pair(100, new MockEvolutionObject()));
	EXPECT_CALL(*evolutionWorld, getHighscoreList()).After(lastIterationExpectation).WillRepeatedly(testing::Return(&fullHighscore));

	evolutionLearningRule->start();
}
