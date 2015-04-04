#include "Edge.hpp"

Edge::Edge(Neuron* prevNeuron_, StandardNeuron* nextNeuron_, float weight_)
{
	prevNeuron = prevNeuron_;
	nextNeuron = nextNeuron_;
	weight = weight_;
}

float Edge::getWeight()
{
	return weight;
}

Neuron* Edge::getPrevNeuron()
{
	return prevNeuron;
}

StandardNeuron* Edge::getNextNeuron()
{
	return nextNeuron;
}

void Edge::setWeigt(float newWeight)
{
	weight = newWeight;
}