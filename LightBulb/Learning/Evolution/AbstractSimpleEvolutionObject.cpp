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
	// Configure the network options depending on the given parameters
	LayeredNetworkOptions options;
	if (biasNeuron) {
		options.useBiasNeuron = true;
	}
	options.neuronsPerLayerCount.push_back(inputDimension);
	options.neuronsPerLayerCount.push_back(outputDimension);
	options.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new IdentityFunction(), new IdentityFunction());

	// Create a new network topology from the adjusted options.
	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);
	
	// Create a neural network from the network topolgy
	neuralNetwork = new NeuralNetwork(layeredNetwork);
	// Randomize all weights (TODO: make the boundaries variable)
	neuralNetwork->getNetworkTopology()->randomizeWeights(-0.5,0.5);

	world = world_;

	// Initialize the mutation strength vector
	resizeMutationStrength(neuralNetwork->getNetworkTopology()->getEdgeCount());
	randomizeMutationStrength();
}


NeuralNetwork* AbstractSimpleEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork;
}

void AbstractSimpleEvolutionObject::doNNCalculation(EvolutionLearningRule& learningRule)
{
	// Get the input
	NeuralNetworkIO<double> input = getNNInput();

	TopologicalOrder topologicalOrder;
	// Calculate the output from the the input
	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork->calculate(input, topologicalOrder, 0, -1, NULL, NULL, false);
	
	// Interpret the output
	interpretNNOutput(learningRule, output.get());
}

AbstractSimpleEvolutionObject::~AbstractSimpleEvolutionObject()
{
	delete(neuralNetwork);
}


void AbstractSimpleEvolutionObject::resetNN()
{
	// Only reset all activations
	neuralNetwork->getNetworkTopology()->resetActivation();
}

AbstractEvolutionObject* AbstractSimpleEvolutionObject::clone(bool addToWorld)
{
	// Create a new object
	AbstractEvolutionObject* newObject = world->addNewObject(addToWorld);
	// Copy all weights
	newObject->getNeuralNetwork()->getNetworkTopology()->copyWeightsFrom(*neuralNetwork->getNetworkTopology());
	// Copy all mutation strengths
	newObject->setMutationStrength(getMutationStrength());
	return newObject;
}
