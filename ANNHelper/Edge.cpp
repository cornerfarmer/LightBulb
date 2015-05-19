#include "Edge.hpp"

Edge::Edge(AbstractNeuron* prevNeuron_, StandardNeuron* nextNeuron_, float weight_)
{
	prevNeuron = prevNeuron_;
	nextNeuron = nextNeuron_;
	weight = weight_;
}

float Edge::getWeight()
{
	return weight;
}

AbstractNeuron* Edge::getPrevNeuron()
{
	return prevNeuron;
}

StandardNeuron* Edge::getNextNeuron()
{
	return nextNeuron;
}

void Edge::setWeight(float newWeight)
{
	weight = newWeight;
}

void Edge::setPrevNeuron(AbstractNeuron* newPrevNeuron)
{
	prevNeuron = newPrevNeuron;
}

void Edge::setNextNeuron(StandardNeuron* newNextNeuron)
{
	nextNeuron = newNextNeuron;
}