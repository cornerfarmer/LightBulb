// Includes
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractCreationCommand.hpp"
#include "Learning/Evolution/AbstractSelectionCommand.hpp"
#include "Learning/Evolution/AbstractFitnessFunction.hpp"
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractExitCondition.hpp"
#include "Learning/Evolution/AbstractReuseCommand.hpp"
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
// Library includes
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

EvolutionLearningRule::EvolutionLearningRule(EvolutionLearningRuleOptions& options_)
	: AbstractEvolutionLearningRule(new EvolutionLearningRuleOptions(options_))
{
	setLoggerToUsedObjects();
}

EvolutionLearningRule::EvolutionLearningRule(EvolutionLearningRuleOptions* options_)
	: AbstractEvolutionLearningRule(options_)
{
	setLoggerToUsedObjects();
}

void EvolutionLearningRule::setLoggerToUsedObjects()
{
	getOptions()->world->setLogger(options->logger);
	getOptions()->world->setLearningState(learningState.get());

	for (auto reuseCommand = getOptions()->reuseCommands.begin(); reuseCommand != getOptions()->reuseCommands.end(); reuseCommand++)
		(*reuseCommand)->setLogger(options->logger);

	for (auto mutationCommand = getOptions()->mutationsCommands.begin(); mutationCommand != getOptions()->mutationsCommands.end(); mutationCommand++)
		(*mutationCommand)->setLogger(options->logger);

	for (auto recombinationCommand = getOptions()->recombinationCommands.begin(); recombinationCommand != getOptions()->recombinationCommands.end(); recombinationCommand++)
		(*recombinationCommand)->setLogger(options->logger);

	for (auto reuseCommand = getOptions()->reuseCommands.begin(); reuseCommand != getOptions()->reuseCommands.end(); reuseCommand++)
		(*reuseCommand)->setLogger(options->logger);

	for (auto creationCommand = getOptions()->creationCommands.begin(); creationCommand != getOptions()->creationCommands.end(); creationCommand++)
		(*creationCommand)->setLogger(options->logger);

	for (auto exitCondition = getOptions()->exitConditions.begin(); exitCondition != getOptions()->exitConditions.end(); exitCondition++)
		(*exitCondition)->setLogger(options->logger);

	for (auto selectionCommand = getOptions()->selectionCommands.begin(); selectionCommand != getOptions()->selectionCommands.end(); selectionCommand++)
		(*selectionCommand)->setLogger(options->logger);
}

//
//LearningState EvolutionLearningRule::doLearning()
//{
//	double bestScore = 0;
//
//	// Do per try
//	for (int currentTry = 0; currentTry < options->maxTries && (currentTry == 0 || bestScore < options->scoreGoal); currentTry++)
//	{
//		initialize();
//
//		if (options->enableDebugOutput)
//			std::cout << "+++++ Try " << currentTry << " +++++" << std::endl;
//
//		// Do while no exit condition has matched
//		bool stopLearning = false;
//		while (!stopLearning)
//		{
//			stopLearning = doEvolutionStep();
//		}
//
//		// Extract the best score from the last try
//		bestScore = options->world->getHighscoreList()->front().first;
//
//		if (options->enableDebugOutput)
//			std::cout << "Best result: " << bestScore << std::endl;
//
//	}
//
//	// Build the learning result
//	LearningState result;
//	result.iterationsNeeded = generation;
//	result.successful = (options->scoreGoal == 0 || options->scoreGoal <= bestScore);
//	result.quality = options->world->getRealScore(options->world->getHighscoreList()->front().second);
//	return result;
//}


bool EvolutionLearningRule::hasLearningSucceeded()
{
	return getOptions()->world->getEvolutionObjects()->size() > 0 && getOptions()->world->getHighscoreList()->front().first >= getOptions()->scoreGoal;
}

void EvolutionLearningRule::initializeTry()
{
	// Reset all
	getOptions()->world->getEvolutionObjects()->clear();
	getOptions()->world->initializeForLearning();
}

std::string EvolutionLearningRule::getName()
{
	return "EvolutionLearningRule";
}

std::vector<std::string> EvolutionLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
	labels.push_back(DATA_SET_FITNESS);
	std::vector<std::string> worldLabels = getOptions()->world->getDataSetLabels();
	labels.insert(labels.end(), worldLabels.begin(), worldLabels.end());
	return labels;
}

bool EvolutionLearningRule::doIteration()
{
	if (getOptions()->world->getEvolutionObjects()->size() > 0)
		learningState->addData(DATA_SET_FITNESS, getOptions()->world->getHighscoreList()->front().first);

	// Reset the world for the next generation
	getOptions()->world->reset();

	log("------------- Generation " + std::to_string(learningState->iterations) + " -----------------", LL_LOW);

	if (getOptions()->world->getEvolutionObjects()->size()>0) {
		// Extract all current objects ordered by their score
		std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> highscore = getOptions()->world->getHighscoreList();
		// This vector will contain all objects for the next generation
		std::vector<AbstractEvolutionObject*> newObjectVector;
		std::map<AbstractEvolutionObject*, int> operationCounter;

		// 5. Step: Reuse some of the evolution objects directly for the next generation
		for (auto reuseCommand = getOptions()->reuseCommands.begin(); reuseCommand != getOptions()->reuseCommands.end(); reuseCommand++)
		{
			(*reuseCommand)->select(highscore.get(), &operationCounter);
		}

		// 6. Step: Mutate some of the evolution objects and use them for the next getOptions()
		for (auto mutationCommand = getOptions()->mutationsCommands.begin(); mutationCommand != getOptions()->mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->select(highscore.get(), &operationCounter);
		}

		// 7. Step: Combine some pairs of evolution objects and use the created ones for the next generation
		for (auto recombinationCommand = getOptions()->recombinationCommands.begin(); recombinationCommand != getOptions()->recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->select(highscore.get(), &operationCounter);
		}

		// 7. Step: Combine some pairs of evolution objects and use the created ones for the next generation
		for (auto recombinationCommand = getOptions()->recombinationCommands.begin(); recombinationCommand != getOptions()->recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->execute(&newObjectVector, &operationCounter, &notUsedObjects);
		}

		// 6. Step: Mutate some of the evolution objects and use them for the next generation
		for (auto mutationCommand = getOptions()->mutationsCommands.begin(); mutationCommand != getOptions()->mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->execute(&newObjectVector, &operationCounter, &notUsedObjects);
		}

		// 5. Step: Reuse some of the evolution objects directly for the next generation
		for (auto reuseCommand = getOptions()->reuseCommands.begin(); reuseCommand != getOptions()->reuseCommands.end(); reuseCommand++)
		{
			(*reuseCommand)->execute(&newObjectVector, &operationCounter, &notUsedObjects);
		}

		// Replace all evolution objects from the last generation with the one from the next generation
		getOptions()->world->setEvolutionObjects(newObjectVector);
	}


	// 1. Step: Create new evolution objects
	for (auto creationCommand = getOptions()->creationCommands.begin(); creationCommand != getOptions()->creationCommands.end(); creationCommand++)
	{
		(*creationCommand)->execute(*getOptions()->world);
	}

	// 2. Step: Execute the simulation and try to rate the evolution objects
	if (getOptions()->world->doSimulationStep()) {
		log(std::to_string(learningState->iterations) + " generations", LL_HIGH);
		learningState->iterations = 0;
		return true;
	}

	// Extract all current objects ordered by their score
	std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> highscore = getOptions()->world->getHighscoreList();

	bool exit = false;
	// 3.Step: Go through all exit conditions
	for (auto exitCondition = getOptions()->exitConditions.begin(); exitCondition != getOptions()->exitConditions.end(); exitCondition++)
	{
		// Evaluate them and connect them with an OR
		exit |= (*exitCondition)->evaluate(highscore.get());
	}
	// If at least one condition was true => stop this try
	if (exit) {
		log("At least one condition is true => exit", LL_HIGH);
		return false;
	}

	// {2,3}.5. Step: Modify the calculated scores
	for (auto fitnessFunction = getOptions()->fitnessFunctions.begin(); fitnessFunction != getOptions()->fitnessFunctions.end(); fitnessFunction++)
	{
		(*fitnessFunction)->execute(highscore.get());
	}

	// 4. Step: Select the relevant evolution objects (Other objects will be deleted)
	for (auto selectionCommand = getOptions()->selectionCommands.begin(); selectionCommand != getOptions()->selectionCommands.end(); selectionCommand++)
	{
		(*selectionCommand)->execute(highscore.get(), getOptions()->world->getEvolutionObjects(), &notUsedObjects);
	}

	// Continue with the next generation
	learningState->iterations++;

	return true;
}

EvolutionLearningRuleOptions* EvolutionLearningRule::getOptions()
{
	return static_cast<EvolutionLearningRuleOptions*>(options.get());
}

void EvolutionLearningRule::doCalculationAfterLearningProcess()
{
	learningState->addData(DATA_SET_FITNESS, getOptions()->world->getHighscoreList()->front().first);
}

