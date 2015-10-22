// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "NetworkTopology/RecurrentLayeredNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Examples/Nature.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "NeuronFactory/SameFunctionsNeuronFactory.hpp"
#include "Neuron/StandardThreshold.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/FermiFunction.hpp"
#include "Function/HyperbolicTangentFunction.hpp"
#include "Function/IdentityFunction.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "Examples/AbstractTile.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/Edge.hpp"

AbstractSimpleEvolutionObject::AbstractSimpleEvolutionObject(AbstractEvolutionWorld* world_, int inputDimension, int outputDimension, bool biasNeuron)
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
	neuralNetwork->getNetworkTopology()->randomizeWeights(0,0.0001);

	/*NeuralNetworkIO<double> input(18);
	input.set(0, 0, 1);
	input.set(0, 5, 1);

	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork->calculate(input, TopologicalOrder(), 0, 1);	*/

	world = world_;

	resizeMutationStrength(neuralNetwork->getNetworkTopology()->getEdgeCount());

	randomizeMutationStrength();
}


NeuralNetwork* AbstractSimpleEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork;
}

void AbstractSimpleEvolutionObject::doNNCalculation(EvolutionLearningRule& learningRule)
{
	NeuralNetworkIO<double> input = getNNInput();
	TopologicalOrder topologicalOrder;
	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork->calculate(input, topologicalOrder, 0, -1, NULL, NULL, false);
	
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

AbstractEvolutionObject* AbstractSimpleEvolutionObject::clone()
{
	AbstractEvolutionObject* newObject = world->addNewObject();
	newObject->getNeuralNetwork()->getNetworkTopology()->copyWeightsFrom(*neuralNetwork->getNetworkTopology());
	newObject->setMutationStrength(getMutationStrength());
	return newObject;
}
