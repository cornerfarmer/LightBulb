#include "Edge.hpp"
#include <cstdlib>
#include <stdexcept>

Edge::Edge(AbstractNeuron* prevNeuron_, StandardNeuron* nextNeuron_, float weight_)
{
	// Check if the given neurons are correct
	if (!prevNeuron_)
		throw std::invalid_argument("The given prevNeuron is not valid");
	if (!nextNeuron_)
		throw std::invalid_argument("The given nextNeuron is not valid");

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

void Edge::randomizeWeight(float randStart, float randEnd)
{
	weight = (float)rand() / RAND_MAX * (randEnd - randStart) + randStart;
}