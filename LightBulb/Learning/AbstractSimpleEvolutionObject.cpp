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

AbstractSimpleEvolutionObject::AbstractSimpleEvolutionObject(EvolutionWorldInterface* world_, int inputDimension, int outputDimension)
{
	RecurrentLayeredNetworkOptions options;

	options.useBiasNeuron = true;
//	options.selfConnectHiddenLayers = true;
	options.neuronsPerLayerCount.push_back(inputDimension);
	options.neuronsPerLayerCount.push_back(20);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(outputDimension);
	options.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new HyperbolicTangentFunction(), new IdentityFunction());

	neuralNetwork = new NeuralNetwork(new RecurrentLayeredNetwork(options));
	neuralNetwork->getNetworkTopology()->randomizeWeights(-0.5, 0.5);

	world = world_;
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
