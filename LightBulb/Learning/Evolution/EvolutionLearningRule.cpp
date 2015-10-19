// Includes
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractCreationCommand.hpp"
#include "Learning/Evolution/AbstractSelectionCommand.hpp"
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractExitCondition.hpp"
#include "Learning/Evolution/AbstractReuseCommand.hpp"
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
	options->world->getEvolutionObjects()->clear();

	int generation = 0;
	while (true)
	{
		options->world->reset();

		if (options->enableDebugOutput)
			std::cout << "------------- Generation " << generation << " -----------------" << std::endl;
		for (auto creationCommand = options->creationCommands.begin(); creationCommand != options->creationCommands.end(); creationCommand++)
		{
			(*creationCommand)->execute(*options->world);
		}

		options->world->doSimulationStep(*this);

		std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> highscore = options->world->getHighscoreList();
		std::vector<AbstractEvolutionObject*> newObjectVector;

		bool exit = true;
		for (auto exitCondition = options->exitConditions.begin(); exitCondition != options->exitConditions.end(); exitCondition++)
		{
			exit &= (*exitCondition)->evaluate(highscore.get());
		}
		if (exit) {
			if (options->enableDebugOutput)
				std::cout << "All conditions are true => exit" << std::endl;
			break;
		}

		for (auto selectionCommand = options->selectionCommands.begin(); selectionCommand != options->selectionCommands.end(); selectionCommand++)
		{
			(*selectionCommand)->execute(highscore.get());
		}

		for (auto reuseCommand = options->reuseCommands.begin(); reuseCommand != options->reuseCommands.end(); reuseCommand++)
		{
			(*reuseCommand)->execute(highscore.get(), &newObjectVector);
		}

		for (auto mutationCommand = options->mutationsCommands.begin(); mutationCommand != options->mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->execute(highscore.get(), &newObjectVector);
		}

		for (auto recombinationCommand = options->recombinationCommands.begin(); recombinationCommand != options->recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->execute(highscore.get(), &newObjectVector);
		}	
	
		options->world->setEvolutionObjects(newObjectVector);

		generation++;
	}

	double bestScore = options->world->getHighscoreList()->front().first;

	if (options->enableDebugOutput)
		std::cout << "Best result: " << bestScore << std::endl;

	LearningResult result;
	result.iterationsNeeded = generation;
	result.successful = (options->scoreGoal == 0 || options->scoreGoal <= bestScore);
	return result;
}

EvolutionLearningRuleOptions* EvolutionLearningRule::getOptions()
{
	return options.get();
}
