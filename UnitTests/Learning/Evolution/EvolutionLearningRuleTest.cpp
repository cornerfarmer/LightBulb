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
	testing::Expectation createExpectation;

	std::vector<std::pair<double, AbstractEvolutionObject*>> emptyHighscore;

	std::vector<std::pair<double, AbstractEvolutionObject*>> unseccessfullHighscore;
	unseccessfullHighscore.push_back(std::make_pair(20, new MockEvolutionObject()));

	{
		testing::InSequence s;

		// Initialize try
		EXPECT_CALL(*evolutionWorld, clearPopulation()).Times(1);
		EXPECT_CALL(*evolutionWorld, initializeForLearning()).Times(1);

		// iteration 0
		EXPECT_CALL(*evolutionWorld, reset()).Times(1);
		createExpectation = EXPECT_CALL(*creationCommand, execute(testing::Ref(*evolutionWorld))).Times(1);
		EXPECT_CALL(*evolutionWorld, doSimulationStep()).WillOnce(testing::Return(false));

		EXPECT_CALL(*exitCondition, evaluate(&unseccessfullHighscore, evolutionLearningRule)).WillOnce(testing::Return(false));
		EXPECT_CALL(*fitnessFunction, execute(&unseccessfullHighscore)).Times(1);
		EXPECT_CALL(*selectionCommand, execute(&unseccessfullHighscore, &objects, testing::_)).Times(1);

		// iteration 1
		EXPECT_CALL(*evolutionWorld, reset()).Times(1);
		EXPECT_CALL(*reuseCommand, select(&unseccessfullHighscore, testing::_)).Times(1);
		EXPECT_CALL(*mutationCommand, select(&unseccessfullHighscore, testing::_)).Times(1);
		EXPECT_CALL(*recombinationCommand, select(&unseccessfullHighscore, testing::_)).Times(1);
		EXPECT_CALL(*recombinationCommand, execute(testing::_, testing::_, testing::_)).Times(1);
		EXPECT_CALL(*mutationCommand, execute(testing::_, testing::_, testing::_)).Times(1);
		EXPECT_CALL(*reuseCommand, execute(testing::_, testing::_, testing::_)).Times(1);
		EXPECT_CALL(*evolutionWorld, setEvolutionObjects(testing::_)).Times(1);

		EXPECT_CALL(*creationCommand, execute(testing::Ref(*evolutionWorld))).Times(1);
		EXPECT_CALL(*evolutionWorld, doSimulationStep()).WillOnce(testing::Return(false));

		lastIterationExpectation = EXPECT_CALL(*exitCondition, evaluate(&unseccessfullHighscore, evolutionLearningRule)).WillOnce(testing::Return(true));
	}

	EXPECT_CALL(*evolutionWorld, getHighscoreList()).WillRepeatedly(testing::Return(&emptyHighscore));

	EXPECT_CALL(*evolutionWorld, getPopulationSize()).After(createExpectation).WillRepeatedly(testing::Return(1));	
	EXPECT_CALL(*evolutionWorld, getHighscoreList()).After(createExpectation).WillRepeatedly(testing::Return(&unseccessfullHighscore));

	std::vector<std::pair<double, AbstractEvolutionObject*>> successfullHighscore;
	successfullHighscore.push_back(std::make_pair(100, new MockEvolutionObject()));
	EXPECT_CALL(*evolutionWorld, getHighscoreList()).After(lastIterationExpectation).WillRepeatedly(testing::Return(&successfullHighscore));

	evolutionLearningRule->start();
}
