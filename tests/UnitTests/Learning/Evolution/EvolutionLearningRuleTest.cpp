#include "UnitTestsPrec.hpp"
#include <LightBulb/Learning/Evolution/EvolutionLearningRule.hpp>
#include <Mocks/MockCreationCommand.hpp>
#include <Mocks/MockMutationCommand.hpp>
#include <Mocks/MockSelectionCommand.hpp>
#include <Mocks/MockExitCondition.hpp>
#include <Mocks/MockFitnessFunction.hpp>
#include <Mocks/MockRecombinationCommand.hpp>
#include <Mocks/MockReuseCommand.hpp>
#include <Mocks/MockEvolutionEnvironment.hpp>
#include <Mocks/MockLogger.hpp>
#include <Mocks/MockIndividual.hpp>

using namespace LightBulb;

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
	MockEvolutionEnvironment* evolutionEnvironment;
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
		evolutionEnvironment = new MockEvolutionEnvironment();

		
		EXPECT_CALL(*mutationCommand, clone()).WillRepeatedly(testing::Return(mutationCommand));
		EXPECT_CALL(*recombinationCommand, clone()).WillRepeatedly(testing::Return(recombinationCommand));
		EXPECT_CALL(*reuseCommand, clone()).WillRepeatedly(testing::Return(reuseCommand));
		EXPECT_CALL(*selectionCommand, clone()).WillRepeatedly(testing::Return(selectionCommand));

		logger = new MockLogger();
	}

	void createLearningRule() {

		EvolutionLearningRuleOptions options;

		MockCreationCommand* creationCommandClone = new MockCreationCommand();
		options.creationCommands.push_back(creationCommandClone);
		EXPECT_CALL(*creationCommandClone, clone()).WillRepeatedly(testing::Return(creationCommand));

		MockExitCondition* exitConditionClone = new MockExitCondition();
		options.exitConditions.push_back(exitConditionClone);
		EXPECT_CALL(*exitConditionClone, clone()).WillRepeatedly(testing::Return(exitCondition));

		MockFitnessFunction* fitnessFunctionClone = new MockFitnessFunction();
		options.fitnessFunctions.push_back(fitnessFunctionClone);
		EXPECT_CALL(*fitnessFunctionClone, clone()).WillRepeatedly(testing::Return(fitnessFunction));

		MockMutationCommand* mutationCommandClone = new MockMutationCommand();
		options.mutationsCommands.push_back(mutationCommandClone);
		EXPECT_CALL(*mutationCommandClone, clone()).WillRepeatedly(testing::Return(mutationCommand));

		MockRecombinationCommand* recombinationCommandClone = new MockRecombinationCommand();
		options.recombinationCommands.push_back(recombinationCommandClone);
		EXPECT_CALL(*recombinationCommandClone, clone()).WillRepeatedly(testing::Return(recombinationCommand));

		MockReuseCommand* reuseCommandClone = new MockReuseCommand();
		options.reuseCommands.push_back(reuseCommandClone);
		EXPECT_CALL(*reuseCommandClone, clone()).WillRepeatedly(testing::Return(reuseCommand));

		MockSelectionCommand* selectionCommandClone = new MockSelectionCommand();
		options.selectionCommands.push_back(selectionCommandClone);
		EXPECT_CALL(*selectionCommandClone, clone()).WillRepeatedly(testing::Return(selectionCommand));

		options.environment = evolutionEnvironment;
		options.logger = logger;
		options.disabledDataSets[DATA_AVG_NEURON_COUNT] = true;
		options.disabledDataSets[DATA_BEST_NEURON_COUNT] = true;

		evolutionLearningRule = new EvolutionLearningRule(options);
	}

	virtual ~EvolutionLearningRuleTest()
	{
		delete evolutionEnvironment;
		delete logger;
		delete evolutionLearningRule;
	}
};

TEST_F(EvolutionLearningRuleTest, setLogger)
{
	EXPECT_CALL(*creationCommand, setLogger(testing::Ref(*logger)));
	EXPECT_CALL(*exitCondition, setLogger(testing::Ref(*logger)));
	EXPECT_CALL(*fitnessFunction, setLogger(testing::Ref(*logger)));
	EXPECT_CALL(*mutationCommand, setLogger(testing::Ref(*logger)));
	EXPECT_CALL(*recombinationCommand, setLogger(testing::Ref(*logger)));
	EXPECT_CALL(*reuseCommand, setLogger(testing::Ref(*logger)));
	EXPECT_CALL(*selectionCommand, setLogger(testing::Ref(*logger)));

	createLearningRule();
}

TEST_F(EvolutionLearningRuleTest, learn)
{
	createLearningRule();

	std::vector<AbstractIndividual*> individuals;
	EXPECT_CALL(*evolutionEnvironment, getIndividuals()).WillRepeatedly(testing::ReturnRef(individuals));
	EXPECT_CALL(*evolutionEnvironment, getPopulationSize()).WillRepeatedly(testing::Return(0));
	testing::Expectation lastIterationExpectation;
	testing::Expectation createExpectation;

	std::vector<std::pair<double, AbstractIndividual*>> emptyHighscore;

	std::vector<std::pair<double, AbstractIndividual*>> unseccessfullHighscore;
	unseccessfullHighscore.push_back(std::make_pair(20, new MockIndividual()));

	{
		testing::InSequence s;

		// Initialize try
		EXPECT_CALL(*evolutionEnvironment, clearPopulation()).Times(1);
		EXPECT_CALL(*evolutionEnvironment, initializeForLearning()).Times(1);

		// iteration 0
		createExpectation = EXPECT_CALL(*creationCommand, execute(testing::Ref(*evolutionEnvironment), testing::_)).Times(1);
		EXPECT_CALL(*evolutionEnvironment, reset()).Times(1);
		EXPECT_CALL(*evolutionEnvironment, doSimulationStep());

		EXPECT_CALL(*fitnessFunction, execute(testing::Ref(unseccessfullHighscore))).Times(1);
		EXPECT_CALL(*exitCondition, evaluate(testing::Ref(unseccessfullHighscore), testing::Ref(*evolutionLearningRule))).WillOnce(testing::Return(false));
		EXPECT_CALL(*selectionCommand, execute(testing::Ref(unseccessfullHighscore), testing::Ref(individuals), testing::_)).Times(1);

		// iteration 1
		EXPECT_CALL(*reuseCommand, select(testing::Ref(unseccessfullHighscore), testing::_)).Times(1);
		EXPECT_CALL(*mutationCommand, select(testing::Ref(unseccessfullHighscore), testing::_)).Times(1);
		EXPECT_CALL(*recombinationCommand, select(testing::Ref(unseccessfullHighscore), testing::_)).Times(1);
		EXPECT_CALL(*recombinationCommand, execute(testing::_, testing::_, testing::_)).Times(1);
		EXPECT_CALL(*mutationCommand, execute(testing::_, testing::_, testing::_)).Times(1);
		EXPECT_CALL(*reuseCommand, execute(testing::_, testing::_, testing::_)).Times(1);
		EXPECT_CALL(*evolutionEnvironment, setIndividuals(testing::_)).Times(1);

		EXPECT_CALL(*creationCommand, execute(testing::Ref(*evolutionEnvironment), testing::_)).Times(1);
		EXPECT_CALL(*evolutionEnvironment, reset()).Times(1);
		EXPECT_CALL(*evolutionEnvironment, doSimulationStep());

		EXPECT_CALL(*fitnessFunction, execute(testing::Ref(unseccessfullHighscore))).Times(1);
		lastIterationExpectation = EXPECT_CALL(*exitCondition, evaluate(testing::Ref(unseccessfullHighscore), testing::Ref(*evolutionLearningRule))).WillOnce(testing::Return(true));

		EXPECT_CALL(*evolutionEnvironment, clearPopulation()).Times(1);
	}

	EXPECT_CALL(*evolutionEnvironment, getHighscoreList()).WillRepeatedly(testing::ReturnRef(emptyHighscore));

	EXPECT_CALL(*evolutionEnvironment, getPopulationSize()).After(createExpectation).WillRepeatedly(testing::Return(1));	
	EXPECT_CALL(*evolutionEnvironment, getHighscoreList()).After(createExpectation).WillRepeatedly(testing::ReturnRef(unseccessfullHighscore));

	std::vector<std::pair<double, AbstractIndividual*>> successfullHighscore;
	successfullHighscore.push_back(std::make_pair(100, new MockIndividual()));
	EXPECT_CALL(*evolutionEnvironment, getHighscoreList()).After(lastIterationExpectation).WillRepeatedly(testing::ReturnRef(successfullHighscore));


	evolutionLearningRule->start();
}
