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
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"
// Library includes
#include <iostream>
#include <algorithm>

EvolutionLearningRule::EvolutionLearningRule(EvolutionLearningRuleOptions& options_)
{
	options.reset(new EvolutionLearningRuleOptions(options_));
}

void EvolutionLearningRule::doMutation(AbstractEvolutionObject& object)
{
	int randEdgeIndex = (double)rand() / RAND_MAX * object.getNeuralNetwork()->getNetworkTopology()->getEdgeCount();
	int edgeIndex = 0;
	for (auto layer = object.getNeuralNetwork()->getNetworkTopology()->getNeurons()->begin(); layer != object.getNeuralNetwork()->getNetworkTopology()->getNeurons()->end(); layer++)
	{
		for (auto neuron = layer->begin(); neuron != layer->end(); neuron++)
		{
			for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++)
			{
				if (edgeIndex++ == randEdgeIndex)
				{
					double d = exp((double)rand() / RAND_MAX * 6 - 4);
					if ((double)rand() / RAND_MAX > 0.5)
						(*edge)->setWeight((*edge)->getWeight() + d);
					else
						(*edge)->setWeight((*edge)->getWeight() - d);
					return;
				}
			}
		}
	}
}

AbstractEvolutionObject* EvolutionLearningRule::doRecombination(AbstractEvolutionObject* object1, AbstractEvolutionObject* object2)
{
	LayeredNetwork* network1 = dynamic_cast<LayeredNetwork*>(object1->getNeuralNetwork()->getNetworkTopology());
	LayeredNetwork* network2 = dynamic_cast<LayeredNetwork*>(object2->getNeuralNetwork()->getNetworkTopology());
	if (!network1 || !network2)
		throw std::logic_error("The network has to be a layered network to do recombination!");
	network1->horizontalMergeWith(*network2);
	for (int layerIndex = 0; layerIndex < network1->getNeurons()->size() - 1; layerIndex++)
	{
		int neuronsToRemove = (*network1->getNeurons())[layerIndex].size() / 2;
		for (int i = 0; i < neuronsToRemove; i++)
		{
			int randomIndex = (float)rand() / RAND_MAX * (*network1->getNeurons())[layerIndex].size();
			network1->removeNeuronFromLayer(layerIndex, randomIndex);
		}
	}
}


LearningResult EvolutionLearningRule::doLearning()
{
	double bestScore = 0;
	int generation = 0;

	// Do per try
	for (int currentTry = 0; currentTry < options->maxTries && (currentTry == 0 || bestScore < options->scoreGoal); currentTry++)
	{
		// Reset all
		generation = 0;
		options->world->getEvolutionObjects()->clear();

		if (options->enableDebugOutput)
			std::cout << "+++++ Try " << currentTry << " +++++" << std::endl;

		// Do while no exit condition has matched
		while (true)
		{
			// Reset the world for the next generation
			options->world->reset();

			if (options->enableDebugOutput)
				std::cout << "------------- Generation " << generation << " -----------------" << std::endl;

			// 1. Step: Create new evolution objects
			for (auto creationCommand = options->creationCommands.begin(); creationCommand != options->creationCommands.end(); creationCommand++)
			{
				(*creationCommand)->execute(*options->world);
			}

			// 2. Step: Execute the simulation and try to rate the evolution objects
			if (options->world->doSimulationStep(*this))
				continue;

			// Extract all current objects ordered by their score
			std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> highscore = options->world->getHighscoreList();
			// This vector will contain all objects for the next generation
			std::vector<AbstractEvolutionObject*> newObjectVector;

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
				break;
			}

			// {2,3}.5. Step: Modify the calculated scores
			for (auto fitnessFunction = options->fitnessFunctions.begin(); fitnessFunction != options->fitnessFunctions.end(); fitnessFunction++)
			{
				(*fitnessFunction)->execute(highscore.get());
			}

			// 4. Step: Select the relevant evolution objects (Other objects will be deleted)
			for (auto selectionCommand = options->selectionCommands.begin(); selectionCommand != options->selectionCommands.end(); selectionCommand++)
			{
				(*selectionCommand)->execute(highscore.get());
			}

			// 5. Step: Reuse some of the evolution objects directly for the next generation
			for (auto reuseCommand = options->reuseCommands.begin(); reuseCommand != options->reuseCommands.end(); reuseCommand++)
			{
				(*reuseCommand)->execute(highscore.get(), &newObjectVector);
			}

			// 6. Step: Mutate some of the evolution objects and use them for the next generation
			for (auto mutationCommand = options->mutationsCommands.begin(); mutationCommand != options->mutationsCommands.end(); mutationCommand++)
			{
				(*mutationCommand)->execute(highscore.get(), &newObjectVector);
			}

			// 7. Step: Combine some pairs of evolution objects and use the created ones for the next generation
			for (auto recombinationCommand = options->recombinationCommands.begin(); recombinationCommand != options->recombinationCommands.end(); recombinationCommand++)
			{
				(*recombinationCommand)->execute(highscore.get(), &newObjectVector);
			}

			// Replace all evolution objects from the last generation with the one from the next generation
			options->world->setEvolutionObjects(newObjectVector);


			std::map<AbstractEvolutionObject*, bool> alreadyDeleted;
			// Make sure all not used objects are deleted properly
			for (auto oldObject = highscore->begin(); oldObject != highscore->end(); oldObject++)
			{
				if (!alreadyDeleted[oldObject->second])
				{
					delete(oldObject->second);
					alreadyDeleted[oldObject->second] = true;
				}
			}

			// Continue with the next generation
			generation++;
		}
	
		// Extract the best score from the last try
		bestScore = options->world->getHighscoreList()->front().first;

		if (options->enableDebugOutput)
			std::cout << "Best result: " << bestScore << std::endl;

	}

	// Build the learning result
	LearningResult result;
	result.iterationsNeeded = generation;
	result.successful = (options->scoreGoal == 0 || options->scoreGoal <= bestScore);
	return result;
}

EvolutionLearningRuleOptions* EvolutionLearningRule::getOptions()
{
	return options.get();
}
