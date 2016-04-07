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
{
	options.reset(new EvolutionLearningRuleOptions(options_));
}


LearningState EvolutionLearningRule::doLearning()
{
	double bestScore = 0;

	// Do per try
	for (int currentTry = 0; currentTry < options->maxTries && (currentTry == 0 || bestScore < options->scoreGoal); currentTry++)
	{
		initialize();

		if (options->enableDebugOutput)
			std::cout << "+++++ Try " << currentTry << " +++++" << std::endl;

		// Do while no exit condition has matched
		bool stopLearning = false;
		while (!stopLearning)
		{
			stopLearning = doEvolutionStep();
		}

		// Extract the best score from the last try
		bestScore = options->world->getHighscoreList()->front().first;

		if (options->enableDebugOutput)
			std::cout << "Best result: " << bestScore << std::endl;

	}

	// Build the learning result
	LearningState result;
	result.iterationsNeeded = generation;
	result.successful = (options->scoreGoal == 0 || options->scoreGoal <= bestScore);
	result.quality = options->world->getRealScore(options->world->getHighscoreList()->front().second);
	return result;
}

void EvolutionLearningRule::initialize()
{
	// Reset all
	generation = 0;
	options->world->getEvolutionObjects()->clear();
	options->world->initializeForLearning();
}

bool EvolutionLearningRule::doEvolutionStep()
{

	// Reset the world for the next generation
	options->world->reset();

	if (options->enableDebugOutput)
		std::cout << "------------- Generation " << generation << " -----------------" << std::endl;

	if (options->world->getEvolutionObjects()->size()>0) {
		// Extract all current objects ordered by their score
		std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> highscore = options->world->getHighscoreList();
		// This vector will contain all objects for the next generation
		std::vector<AbstractEvolutionObject*> newObjectVector;
		std::map<AbstractEvolutionObject*, int> operationCounter;

		// 5. Step: Reuse some of the evolution objects directly for the next generation
		for (auto reuseCommand = options->reuseCommands.begin(); reuseCommand != options->reuseCommands.end(); reuseCommand++)
		{
			(*reuseCommand)->select(highscore.get(), &operationCounter);
		}

		// 6. Step: Mutate some of the evolution objects and use them for the next generation
		for (auto mutationCommand = options->mutationsCommands.begin(); mutationCommand != options->mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->select(highscore.get(), &operationCounter);
		}

		// 7. Step: Combine some pairs of evolution objects and use the created ones for the next generation
		for (auto recombinationCommand = options->recombinationCommands.begin(); recombinationCommand != options->recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->select(highscore.get(), &operationCounter);
		}

		// 7. Step: Combine some pairs of evolution objects and use the created ones for the next generation
		for (auto recombinationCommand = options->recombinationCommands.begin(); recombinationCommand != options->recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->execute(&newObjectVector, &operationCounter, &notUsedObjects);
		}

		// 6. Step: Mutate some of the evolution objects and use them for the next generation
		for (auto mutationCommand = options->mutationsCommands.begin(); mutationCommand != options->mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->execute(&newObjectVector, &operationCounter, &notUsedObjects);
		}

		// 5. Step: Reuse some of the evolution objects directly for the next generation
		for (auto reuseCommand = options->reuseCommands.begin(); reuseCommand != options->reuseCommands.end(); reuseCommand++)
		{
			(*reuseCommand)->execute(&newObjectVector, &operationCounter, &notUsedObjects);
		}

		// Replace all evolution objects from the last generation with the one from the next generation
		options->world->setEvolutionObjects(newObjectVector);
	}


	// 1. Step: Create new evolution objects
	for (auto creationCommand = options->creationCommands.begin(); creationCommand != options->creationCommands.end(); creationCommand++)
	{
		(*creationCommand)->execute(*options->world);
	}

	// 2. Step: Execute the simulation and try to rate the evolution objects
	if (options->world->doSimulationStep()) {
		std::cout << generation << " generations" << std::endl;
		generation = 0;
		return false;
	}

	// Extract all current objects ordered by their score
	std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> highscore = options->world->getHighscoreList();

	bool exit = false;
	// 3.Step: Go through all exit conditions
	for (auto exitCondition = options->exitConditions.begin(); exitCondition != options->exitConditions.end(); exitCondition++)
	{
		// Evaluate them and connect them with an OR
		exit |= (*exitCondition)->evaluate(highscore.get());
	}
	// If at least one condition was true => stop this try
	if (exit) {
		if (options->enableDebugOutput)
			std::cout << "At least one condition is true => exit" << std::endl;
		return true;
	}

	// {2,3}.5. Step: Modify the calculated scores
	for (auto fitnessFunction = options->fitnessFunctions.begin(); fitnessFunction != options->fitnessFunctions.end(); fitnessFunction++)
	{
		(*fitnessFunction)->execute(highscore.get());
	}

	// 4. Step: Select the relevant evolution objects (Other objects will be deleted)
	for (auto selectionCommand = options->selectionCommands.begin(); selectionCommand != options->selectionCommands.end(); selectionCommand++)
	{
		(*selectionCommand)->execute(highscore.get(), options->world->getEvolutionObjects(), &notUsedObjects);
	}

	// Continue with the next generation
	generation++;

	return false;
}

EvolutionLearningRuleOptions* EvolutionLearningRule::getOptions()
{
	return options.get();
}
