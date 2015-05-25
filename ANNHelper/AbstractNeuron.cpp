#include "AbstractNeuron.hpp"
#include "Edge.hpp"
#include "StandardNeuron.hpp"

AbstractNeuron::~AbstractNeuron()
{
	for (std::list<Edge*>::iterator edge = efferentEdges.begin(); edge != efferentEdges.end(); edge++)
	{
		delete(*edge);
	}
}

AbstractNeuron::AbstractNeuron()
{
	// Set the activation to 0
	activation = 0;
}

void AbstractNeuron::addNextNeuron(StandardNeuron* newNextNeuron, float weight)
{
	// Create a new edge between this and the newPrevNeuron
	Edge* newEdge = new Edge(this, newNextNeuron, weight);
	// Add the newEdge to the afferentEdge list
	efferentEdges.push_back(newEdge);
	// Add the newEdge also to the newPrevNeuron
	newNextNeuron->addPrevNeuron(newEdge);	
}

void AbstractNeuron::addNextNeuron(Edge* newEdge)
{
	// Add the newEdge to the afferentEdge list
	efferentEdges.push_back(newEdge);
}

float AbstractNeuron::getActivation()
{
	return activation;
}

std::list<Edge*>* AbstractNeuron::getEfferentEdges()
{
	return &efferentEdges;
}

void AbstractNeuron::resetActivation()
{
	activation = 0;
}