// Includes
#include "NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "NeuronDescription/NeuronDescription.hpp"
// Library includes

namespace LightBulb
{
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

	AbstractNeuronDescriptionFactory* SameNeuronDescriptionFactory::getCopy() const
	{
		return new SameNeuronDescriptionFactory(*this);
	}

	const AbstractActivationFunction& SameNeuronDescriptionFactory::getOutputActivationFunction() const
	{
		return neuronDescription->getActivationFunction();
	}

	const AbstractActivationFunction& SameNeuronDescriptionFactory::getInnerActivationFunction() const
	{
		return neuronDescription->getActivationFunction();
	}
}