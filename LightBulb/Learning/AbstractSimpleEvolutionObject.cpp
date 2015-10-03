// Includes
#include "Learning\AbstractSimpleEvolutionObject.hpp"
#include "NetworkTopology\RecurrentLayeredNetwork.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Examples\Nature.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "NeuronFactory\SameFunctionsNeuronFactory.hpp"
#include "Neuron\StandardThreshold.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\FermiFunction.hpp"
#include "Function\HyperbolicTangentFunction.hpp"
#include "Function\IdentityFunction.hpp"
#include "Learning\EvolutionLearningRule.hpp"
#include "Examples\AbstractTile.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"

AbstractSimpleEvolutionObject::AbstractSimpleEvolutionObject(EvolutionWorldInterface* world_, int inputDimension, int outputDimension, bool biasNeuron)
{
	LayeredNetworkOptions options;
	if (biasNeuron) {
		options.useBiasNeuron = true;
	}
	options.neuronsPerLayerCount.push_back(inputDimension);
	options.neuronsPerLayerCount.push_back(outputDimension);
	options.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new IdentityFunction(), new IdentityFunction());

	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);

	int n = 0;
	for (auto neuron = layeredNetwork->getNeurons()->front().begin(); neuron != layeredNetwork->getNeurons()->front().end(); neuron++, n++)
	{
		int e = 0;
		for (auto edge = (*neuron)->getAfferentEdges()->begin(); edge != (*neuron)->getAfferentEdges()->end(); edge++, e++)
		{
			if (n * 2 == e || n * 2 + 1 == e)
				(*edge)->setWeight(-0.5);
			else if (e == 18)
				(*edge)->setWeight(0.25);
			else
				(*edge)->setWeight(0);
		}
	}

	
	neuralNetwork = new NeuralNetwork(layeredNetwork);
	neuralNetwork->getNetworkTopology()->randomizeWeights(-1, 1);

	/*NeuralNetworkIO<double> input(18);
	input.set(0, 0, 1);
	input.set(0, 5, 1);

	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork->calculate(input, TopologicalOrder(), 0, 1);	*/

	world = world_;

	mutationStrength.resize(neuralNetwork->getNetworkTopology()->getEdgeCount());

	randomizeMutationStrength();
}

void AbstractSimpleEvolutionObject::randomizeMutationStrength()
{
	for (auto mutationStrengthValue = mutationStrength.begin(); mutationStrengthValue != mutationStrength.end(); mutationStrengthValue++) 
	{
		*mutationStrengthValue = (float)rand() / RAND_MAX * 2 - 1;
	}
}

std::vector<double>* AbstractSimpleEvolutionObject::getMutationStrength()
{
	return &mutationStrength;
}

NeuralNetwork* AbstractSimpleEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork;
}

void AbstractSimpleEvolutionObject::doNNCalculation(EvolutionLearningRule& learningRule)
{
	NeuralNetworkIO<double> input = getNNInput();
	
	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork->calculate(input, TopologicalOrder(), 0, -1, NULL, NULL, false);	
	
	interpretNNOutput(learningRule, output.get());
}

AbstractSimpleEvolutionObject::~AbstractSimpleEvolutionObject()
{
	delete(neuralNetwork);
}


void AbstractSimpleEvolutionObject::resetNN()
{
	neuralNetwork->getNetworkTopology()->resetActivation();
}

EvolutionObjectInterface* AbstractSimpleEvolutionObject::clone()
{
	EvolutionObjectInterface* newObject = world->addNewObject();
	newObject->getNeuralNetwork()->getNetworkTopology()->copyWeightsFrom(*neuralNetwork->getNetworkTopology());
	return newObject;
}
