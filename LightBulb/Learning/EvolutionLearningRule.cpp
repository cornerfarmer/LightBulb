// Includes
#include "Learning\EvolutionLearningRule.hpp"
#include "Learning\EvolutionObjectInterface.hpp"
#include "Learning\EvolutionWorldInterface.hpp"
#include "Learning\AbstractCreationCommand.hpp"
#include "Learning\AbstractSelectionCommand.hpp"
#include "Learning\AbstractMutationCommand.hpp"
#include "Learning\AbstractRecombinationCommand.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"
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

EvolutionObjectInterface* EvolutionLearningRule::doRecombination(EvolutionObjectInterface* object1, EvolutionObjectInterface* object2)
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

bool EvolutionLearningRule::doLearning(EvolutionWorldInterface& world)
{
	int step = 1;
	while (true)
	{
		for (auto creationCommand = options->creationCommands.begin(); creationCommand != options->creationCommands.end(); creationCommand++)
		{
			(*creationCommand)->execute(world);
		}

		world.doSimulationStep(*this);

		std::unique_ptr<std::vector<std::pair<double, EvolutionObjectInterface*>>> highscore = world.getHighscoreList();
		std::vector<EvolutionObjectInterface*> newObjectVector;

		for (auto selectionCommand = options->selectionCommands.begin(); selectionCommand != options->selectionCommands.end(); selectionCommand++)
		{
			(*selectionCommand)->execute(highscore.get(), &newObjectVector);
		}

		for (auto mutationCommand = options->mutationsCommands.begin(); mutationCommand != options->mutationsCommands.end(); mutationCommand++)
		{
			(*mutationCommand)->execute(this, highscore.get(), &newObjectVector);
		}


		for (auto recombinationCommand = options->recombinationCommands.begin(); recombinationCommand != options->recombinationCommands.end(); recombinationCommand++)
		{
			(*recombinationCommand)->execute(this, highscore.get(), &newObjectVector);
		}

		world.setEvolutionObjects(newObjectVector);
		world.reset();
	}
	return true;
}