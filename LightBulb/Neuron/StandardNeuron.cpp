// Includes
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "Function\AbstractInputFunction.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "Function\AbstractOutputFunction.hpp"
#include "Neuron\AbstractThreshold.hpp"

StandardNeuron::~StandardNeuron()
{
	delete(inputFunction);
	delete(activationFunction);
	delete(outputFunction);
	delete(threshold);
}

StandardNeuron::StandardNeuron(AbstractThreshold* threshold_, AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_)
{
	if (!threshold_)
		throw std::invalid_argument("The given threshold is not valid");
	if (!inputFunction_)
		throw std::invalid_argument("The given inputFunction is not valid");
	if (!activationFunction_)
		throw std::invalid_argument("The given activationFunction is not valid");
	if (!outputFunction_)
		throw std::invalid_argument("The given outputFunction is not valid");

	inputFunction = inputFunction_;
	activationFunction = activationFunction_;
	outputFunction = outputFunction_;

	threshold = threshold_;
	netInput = 0;
	additionalInput = 0;
}

void StandardNeuron::addPrevNeuron(AbstractNeuron* newPrevNeuron, double weight)
{
	// Create a new edge between this and the newPrevNeuron
	Edge* newEdge = new Edge(newPrevNeuron, this, weight);
	// Add the newEdge to the afferentEdge list
	afferentEdges.push_back(newEdge);
	// Add the newEdge also to the newPrevNeuron
	newPrevNeuron->addNextNeuron(newEdge);	
}

void StandardNeuron::addPrevNeuron(Edge* newEdge)
{
	// Add the newEdge to the afferentEdge list
	afferentEdges.push_back(newEdge);
}

void StandardNeuron::removeAfferentEdge(Edge* edgeToRemove)
{
	// Go through all edges and delete edgeToRemove
	for (auto edge = afferentEdges.begin(); edge != afferentEdges.end(); edge++)
	{
		if (*edge == edgeToRemove)
		{
			afferentEdges.erase(edge);
			break;
		}
	}
}

void StandardNeuron::refreshActivation()
{
	// Calc the activation from the input
	activation = activationFunction->execute(netInput, threshold);
	// Calc the output activation from the activation
	activation = outputFunction->execute(activation);
}

void StandardNeuron::refreshNetInput(std::map<AbstractNeuron*, double>* neuronOutputCache)
{
	// Calc the input from all afferentEdges
	netInput = inputFunction->execute(afferentEdges, threshold, additionalInput, neuronOutputCache);
}

std::list<Edge*>* StandardNeuron::getAfferentEdges()
{
	return &afferentEdges;
}

double StandardNeuron::getNetInput()
{
	return netInput;
}

double StandardNeuron::executeDerivationOnActivationFunction(double input)
{
	return activationFunction->executeDerivation(input, threshold);
}

AbstractActivationFunction* StandardNeuron::getActivationFunction()
{
	return activationFunction;
}

AbstractThreshold* StandardNeuron::getThreshold()
{
	return threshold;
}

void StandardNeuron::setAdditionalInput(double newAdditionalInput)
{
	additionalInput = newAdditionalInput;
}

void StandardNeuron::injectActivation(double newActivation)
{
	activation = newActivation;
}