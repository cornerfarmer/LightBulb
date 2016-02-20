// Includes
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "Neuron/StandardNeuron.hpp"

AbstractNeuron::~AbstractNeuron()
{
	for (auto edge = efferentEdges.begin(); edge != efferentEdges.end(); edge++)
	{
		delete(*edge);
	}
}

AbstractNeuron::AbstractNeuron()
{
	resetActivation();
}

void AbstractNeuron::addNextNeuron(StandardNeuron* newNextNeuron, double weight)
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

double AbstractNeuron::getActivation()
{
	return activation;
}

std::list<Edge*>* AbstractNeuron::getEfferentEdges()
{
	return &efferentEdges;
}

void AbstractNeuron::resetActivation()
{
	// Set the activation to 0
	activation = 0;
}

void AbstractNeuron::removeEfferentEdge(Edge* edgeToRemove)
{
	// Go through all edges and delete edgeToRemove
	for (auto edge = efferentEdges.begin(); edge != efferentEdges.end(); edge++)
	{
		if (*edge == edgeToRemove)
		{
			efferentEdges.erase(edge);
			break;
		}
	}
}