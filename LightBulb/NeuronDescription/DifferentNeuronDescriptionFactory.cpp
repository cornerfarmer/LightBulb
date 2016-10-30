// Includes
#include "NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "NeuronDescription/NeuronDescription.hpp"
// Library includes

namespace LightBulb
{
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
		outputNeuronDescription.reset(dynamic_cast<NeuronDescription*>(obj.outputNeuronDescription->clone()));
		innerNeuronDescription.reset(dynamic_cast<NeuronDescription*>(obj.innerNeuronDescription->clone()));
	}

	NeuronDescription* DifferentNeuronDescriptionFactory::createInnerNeuronDescription()
	{
		return dynamic_cast<NeuronDescription*>(innerNeuronDescription->clone());
	}

	NeuronDescription* DifferentNeuronDescriptionFactory::createOutputNeuronDescription()
	{
		return dynamic_cast<NeuronDescription*>(outputNeuronDescription->clone());
	}

	AbstractCloneable* DifferentNeuronDescriptionFactory::clone() const
	{
		return new DifferentNeuronDescriptionFactory(*this);
	}

	const AbstractActivationFunction& DifferentNeuronDescriptionFactory::getOutputActivationFunction() const
	{
		return outputNeuronDescription->getActivationFunction();
	}

	const AbstractActivationFunction& DifferentNeuronDescriptionFactory::getInnerActivationFunction() const
	{
		return innerNeuronDescription->getActivationFunction();
	}
}