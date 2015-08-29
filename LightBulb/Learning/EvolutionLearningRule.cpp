// Includes
#include "Learning\EvolutionLearningRule.hpp"
#include "Learning\EvolutionObjectInterface.hpp"
#include "Learning\EvolutionWorldInterface.hpp"
#include "Learning\AbstractCreationCommand.hpp"
#include "Learning\AbstractSelectionCommand.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"

EvolutionLearningRule::EvolutionLearningRule(EvolutionLearningRuleOptions& options_)
{
	options.reset(new EvolutionLearningRuleOptions(options_));
}

void EvolutionLearningRule::doMutation(EvolutionObjectInterface& object)
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

EvolutionObjectInterface* EvolutionLearningRule::doRecombination(std::vector<EvolutionObjectInterface*> object)
{
	return NULL;
}

bool EvolutionLearningRule::doLearning(EvolutionWorldInterface& world)
{
	while (true)
	{
		for (auto creationCommand = options->creationCommands.begin(); creationCommand != options->creationCommands.end(); creationCommand++)
		{
			(*creationCommand)->execute(world);
		}

		world.doSimulationStep(*this);

		for (auto selectionCommand = options->selectionCommands.begin(); selectionCommand != options->selectionCommands.end(); selectionCommand++)
		{
			(*selectionCommand)->execute(world);
		}

		world.reset();
	}
	return true;
}