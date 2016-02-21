// Includes
#include "NeuronFactory/SameNeuronDescriptionFactory.hpp"
#include "Function/AbstractInputFunction.hpp"
#include "Neuron/NeuronDescription.hpp"
// Library includes

SameNeuronDescriptionFactory::SameNeuronDescriptionFactory(NeuronDescription* neuronDescription_)
{
	// Check if all given options are correct
	if (!neuronDescription_)
		throw std::invalid_argument("The given neuronDescription is not valid");

	neuronDescription.reset(neuronDescription_);
}

SameNeuronDescriptionFactory::SameNeuronDescriptionFactory(const SameNeuronDescriptionFactory &obj)
{
	neuronDescription.reset(obj.neuronDescription->getCopy());
}

NeuronDescription* SameNeuronDescriptionFactory::createInnerNeuronDescription()
{
	return neuronDescription->getCopy();
}

NeuronDescription* SameNeuronDescriptionFactory::createOutputNeuronDescription()
{
	return neuronDescription->getCopy();
}

AbstractNeuronDescriptionFactory* SameNeuronDescriptionFactory::getCopy()
{
	return new SameNeuronDescriptionFactory(*this);
}

AbstractActivationFunction* SameNeuronDescriptionFactory::getOutputActivationFunction()
{
	return neuronDescription->getActivationFunction();
}
