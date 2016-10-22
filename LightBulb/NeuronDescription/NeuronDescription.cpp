// Includes
#include "NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	NeuronDescription::NeuronDescription(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_)
	{
		inputFunction.reset(inputFunction_);
		activationFunction.reset(activationFunction_);
	}

	NeuronDescription* NeuronDescription::getCopy() const
	{
		return new NeuronDescription(inputFunction->getInputFunctionCopy(), activationFunction->getActivationFunctionCopy());
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