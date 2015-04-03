#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "InputFunction.hpp"
#include "ActivationFunction.hpp"
#include "OutputFunction.hpp"

StandardNeuron::~StandardNeuron()
{

}

StandardNeuron::StandardNeuron(InputFunction* inputFunction_, ActivationFunction* activationFunction_, OutputFunction* outputFunction_)
{
	inputFunction = inputFunction_;
	activationFunction = activationFunction_;
	outputFunction = outputFunction_;
	threshold = 0;
}

void StandardNeuron::addPrevNeuron(Neuron* newPrevNeuron, float weight)
{
	// Create a new edge between this and the newPrevNeuron
	Edge* newEdge = new Edge(newPrevNeuron, this, weight);
	// Add the newEdge to the afferentEdge list
	afferentEdges.push_front(newEdge);
	// Add the newEdge also to the newPrevNeuron
	newPrevNeuron->addNextNeuron(newEdge);	
}

void StandardNeuron::addPrevNeuron(Edge* newEdge)
{
	// Add the newEdge to the afferentEdge list
	afferentEdges.push_front(newEdge);
}

void StandardNeuron::refreshActivation()
{
	// Calc the input from all afferentEdges
	activation = inputFunction->execute(afferentEdges);
	// Calc the activation from the input
	activation = activationFunction->execute(activation);
	// Calc the output activation from the activation
	activation = outputFunction->execute(activation);
}