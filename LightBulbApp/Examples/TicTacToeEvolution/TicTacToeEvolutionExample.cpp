#include "TicTacToeEvolutionExample.hpp"
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/ConstantReuseCommand.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <Learning/Evolution/SharedSamplingCombiningStrategy.hpp>
#include <Learning/Evolution/AbstractHallOfFameAlgorithm.hpp>
#include <Learning/Evolution/RandomHallOfFameAlgorithm.hpp>
#include <Examples/TicTacToeEvolution/TicTacToe.hpp>
#include <Learning/Evolution/SharedCoevolutionFitnessFunction.hpp>
#include <Learning/Evolution/PerfectObjectFoundCondition.hpp>
#include <Learning/Evolution/BipartiteEvolutionLearningRule.hpp>
#include <fstream>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include "TicTacToeGameFactory.hpp"
#include <Learning/Evolution/RandomCombiningStrategy.hpp>
#include <TrainingPlans/DoublePreference.hpp>
#include <TrainingPlans/IntegerPreference.hpp>

//
//void doTicTacToeEvolutionExample()
//{
//	
//#define TICTACTOE_SINGLE
//#ifdef TICTACTOE_SINGLE
//	LearningState result = learningRule.doLearning();
//	std::cout << "total generations: " << result.iterationsNeeded << std::endl;
//
//#else
//	ticTacToe.setDebugOutput(false);
//	LearningRuleAnalyserOptions analyserOptions;
//	analyserOptions.learningRule = &learningRule;
//	analyserOptions.changableParameters.push_back(new ChangeableNumber<double, TicTacToe>(&ticTacToe, &TicTacToe::setMaxDistanceShrinkFactor, 0.5, 0.1, 0.9, "shr"));
//
//	analyserOptions.calculationsPerParameterCombination = 1;
//	analyserOptions.useQualityInsteadOfSuccessful = true;
//
//	LearningRuleAnalyser learningRuleAnalyser(analyserOptions);
//
//	learningRuleAnalyser.execute();
//#endif
//
//	TicTacToeDrawerOptions ticTacToeDrawerOptions;
//	ticTacToeDrawerOptions.width = 600;
//	ticTacToeDrawerOptions.height = 600;
//	ticTacToeDrawerOptions.ticTacToe = &ticTacToe1;
//	TicTacToeDrawer ticTacToeDrawer(ticTacToeDrawerOptions);
//
//	sf::RenderWindow window(sf::VideoMode(1300, 1000), "LightBulb!");
//
//	TicTacToeKI* bestAI = static_cast<TicTacToeKI*>(ticTacToe1.getHighscoreList()->front().second);// ticTacToe.getBestAIs()->back();
//
//	SynapticExporter exporter;
//	std::string json = exporter.execute(bestAI->getNeuralNetwork());
//	std::ofstream myfile;
//	myfile.open("bestTicTacToeAI.txt");
//	myfile << json;
//	myfile.close();
//
//	ticTacToe1.startNewGame(1);
//	bestAI->resetNN();
//	bestAI->setTicTacToe(&ticTacToe1);
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//			else if (event.type == sf::Event::MouseButtonPressed) {
//				if (ticTacToe1.hasGameFinished()) {
//					ticTacToe1.startNewGame(1);
//					bestAI->resetNN();
//				}
//				else if (ticTacToeDrawer.handleMouseInputEvent(event)) {
//					if (!ticTacToe1.hasGameFinished()) {
//						bestAI->doNNCalculation();
//						if (ticTacToe1.hasGameFinished())
//							std::cout << "AI has failed" << std::endl;
//					}
//					else
//						std::cout << "Player has failed" << std::endl;
//				}
//			}
//		}
//
//		window.clear();
//		ticTacToeDrawer.recalculateAllValues();
//		ticTacToeDrawer.draw(window);
//		//networkTopologyDrawer.draw(window);
//		window.display();
//	}
//}

#define PREFERENCE_POPULATION_SIZE "Population size"
#define PREFERENCE_MUTATION_PERCENTAGE "Mutation percentage"
#define PREFERENCE_RECOMBINATION_PERCENTAGE "Recombination percentage"
#define PREFERENCE_COMPETITIONS_SIZE "Competitions per object"
#define PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE "Hall of fame competitions"

AbstractLearningRule* TicTacToeEvolutionExample::createLearningRate()
{

	EvolutionLearningRuleOptions options;

	options.creationCommands.push_back(new ConstantCreationCommand(getIntegerPreference(PREFERENCE_POPULATION_SIZE)));
	options.exitConditions.push_back(new PerfectObjectFoundCondition(200));
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 16));
	options.selectionCommands.push_back(new BestSelectionCommand(getIntegerPreference(PREFERENCE_POPULATION_SIZE)));
	options.mutationsCommands.push_back(new ConstantMutationCommand(new MutationAlgorithm(1.6), new RandomSelector(new RankBasedRandomFunction()), getDoublePreference(PREFERENCE_MUTATION_PERCENTAGE)));
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), getDoublePreference(PREFERENCE_RECOMBINATION_PERCENTAGE)));
	//options.fitnessFunctions.push_back(new FitnessSharingFitnessFunction(150));
	fillDefaultEvolutionLearningRule1Options(&options);

	//options.recombinationCommands.push_back(new ConstantRecombinationCommand(7));

	EvolutionLearningRule* learningRule1 = new EvolutionLearningRule(options);
	fillDefaultEvolutionLearningRule2Options(&options);
	EvolutionLearningRule* learningRule2 = new EvolutionLearningRule(options);

	BipartiteEvolutionLearningRuleOptions bipartiteOptions;
	bipartiteOptions.learningRule1 = learningRule1;
	bipartiteOptions.learningRule2 = learningRule2;
	fillDefaultLearningRuleOptions(&bipartiteOptions);

	return new BipartiteEvolutionLearningRule(bipartiteOptions);
}

AbstractEvolutionWorld* TicTacToeEvolutionExample::createWorld()
{
	cs1 = new SharedSamplingCombiningStrategy(getIntegerPreference(PREFERENCE_COMPETITIONS_SIZE));

	hof1 = new RandomHallOfFameAlgorithm(getIntegerPreference(PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE));
	hof2 = new RandomHallOfFameAlgorithm(getIntegerPreference(PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE));

	return new TicTacToe(false, cs1, new SharedCoevolutionFitnessFunction(), hof1, hof2);
}

AbstractEvolutionWorld* TicTacToeEvolutionExample::createParasiteWorld()
{
	cs2 = new SharedSamplingCombiningStrategy(getIntegerPreference(PREFERENCE_COMPETITIONS_SIZE));

	TicTacToe* ticTacToe2 = new TicTacToe(true, cs2, new SharedCoevolutionFitnessFunction(), hof2, hof1);
	cs1->setSecondWorld(ticTacToe2);
	cs2->setSecondWorld(static_cast<TicTacToe*>(world.get()));
	return ticTacToe2;
}

TicTacToeEvolutionExample::TicTacToeEvolutionExample()
{
	addCustomSubApp(new TicTacToeGameFactory());
	addPreference(new DoublePreference(PREFERENCE_MUTATION_PERCENTAGE, 1.8, 0, 3));
	addPreference(new DoublePreference(PREFERENCE_RECOMBINATION_PERCENTAGE, 0.3, 0, 3));
	addPreference(new IntegerPreference(PREFERENCE_POPULATION_SIZE, 500, 1, 1000));
	addPreference(new IntegerPreference(PREFERENCE_COMPETITIONS_SIZE, 100, 1, 1000));
	addPreference(new IntegerPreference(PREFERENCE_HALLOFFAME_COMPETITIONS_SIZE, 50, 1, 1000));
}

std::string TicTacToeEvolutionExample::getName()
{
	return "TicTacToe evolution example";
}

std::string TicTacToeEvolutionExample::getDescription()
{
	return "Evolution of a perfect TicTacToe KI with the bipartite evolution learning rule.";
}

AbstractTrainingPlan* TicTacToeEvolutionExample::getCopy()
{
	return new TicTacToeEvolutionExample();
}

std::string TicTacToeEvolutionExample::getLearningRuleName()
{
	return BipartiteEvolutionLearningRule::getName();
}

