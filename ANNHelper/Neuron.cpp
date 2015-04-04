#include "Neuron.hpp"
#include "Edge.hpp"
#include "StandardNeuron.hpp"

Neuron::~Neuron()
{

}

Neuron::Neuron()
{
	// Set the activation to 0
	activation = 0;
}

void Neuron::addNextNeuron(StandardNeuron* newNextNeuron, float weight)
{
	// Create a new edge between this and the newPrevNeuron
	Edge* newEdge = new Edge(this, newNextNeuron, weight);
	// Add the newEdge to the afferentEdge list
	efferentEdges.push_front(newEdge);
	// Add the newEdge also to the newPrevNeuron
	newNextNeuron->addPrevNeuron(newEdge);	
}

void Neuron::addNextNeuron(Edge* newEdge)
{
	// Add the newEdge to the afferentEdge list
	efferentEdges.push_front(newEdge);
}

float Neuron::getActivation()
{
	return activation;
}

std::list<Edge*>* Neuron::getEfferentEdges()
{
	return &efferentEdges;
}