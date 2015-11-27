// Includes
#include "Neuron/Edge.hpp"
// Library includes
#include <cstdlib>
#include <stdexcept>

Edge::Edge(AbstractNeuron* prevNeuron_, StandardNeuron* nextNeuron_, double weight_)
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

double Edge::getWeight()
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

void Edge::setWeight(double newWeight)
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

void Edge::randomizeWeight(double randStart, double randEnd)
{
	weight = randGenerator.next() * (randEnd - randStart) + randStart;
}