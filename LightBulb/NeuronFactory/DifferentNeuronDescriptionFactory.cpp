// Includes
#include "NeuronFactory/DifferentNeuronDescriptionFactory.hpp"
#include "Function/AbstractInputFunction.hpp"
#include "Neuron/NeuronDescription.hpp"
// Library includes

DifferentNeuronDescriptionFactory::DifferentNeuronDescriptionFactory(NeuronDescription* innerNeuronDescription_, NeuronDescription* outputNeuronDescription_)
{
	// Check if all given options are correct
	if (!innerNeuronDescription_)
		throw std::invalid_argument("The given innerNeuronDescription is not valid");
	if (!outputNeuronDescription_)
		throw std::invalid_argument("The given outputNeuronDescription is not valid");

	outputNeuronDescription.reset(outputNeuronDescription_);
	innerNeuronDescription.reset(innerNeuronDescription_);
}

DifferentNeuronDescriptionFactory::DifferentNeuronDescriptionFactory(const DifferentNeuronDescriptionFactory &obj)
{
	outputNeuronDescription.reset(obj.outputNeuronDescription->getCopy());
	innerNeuronDescription.reset(obj.innerNeuronDescription->getCopy());
}

NeuronDescription* DifferentNeuronDescriptionFactory::createInnerNeuronDescription()
{
	return innerNeuronDescription->getCopy();
}

NeuronDescription* DifferentNeuronDescriptionFactory::createOutputNeuronDescription()
{
	return outputNeuronDescription->getCopy();
}

AbstractNeuronDescriptionFactory* DifferentNeuronDescriptionFactory::getCopy()
{
	return new DifferentNeuronDescriptionFactory(*this);
}

AbstractActivationFunction* DifferentNeuronDescriptionFactory::getOutputActivationFunction()
{
	return outputNeuronDescription->getActivationFunction();
}
