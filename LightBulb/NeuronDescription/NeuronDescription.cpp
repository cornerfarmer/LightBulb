// Includes
#include "NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	NeuronDescription::NeuronDescription(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_)
	{
		inputFunction.reset(inputFunction_);
		activationFunction.reset(activationFunction_);
	}

	NeuronDescription::NeuronDescription(const NeuronDescription& other)
	{
		inputFunction.reset(dynamic_cast<AbstractInputFunction*>(other.inputFunction->clone()));
		activationFunction.reset(dynamic_cast<AbstractActivationFunction*>(other.activationFunction->clone()));
	}

	AbstractCloneable* NeuronDescription::clone() const
	{
		return new NeuronDescription(*this);
	}

	const AbstractInputFunction& NeuronDescription::getInputFunction() const
	{
		return *inputFunction.get();
	}

	const AbstractActivationFunction& NeuronDescription::getActivationFunction() const
	{
		return *activationFunction.get();
	}
}