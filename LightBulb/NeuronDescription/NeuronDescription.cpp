// Includes
#include "NeuronDescription/NeuronDescription.hpp"


NeuronDescription::NeuronDescription(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_)
{
	inputFunction.reset(inputFunction_);
	activationFunction.reset(activationFunction_);
}

NeuronDescription* NeuronDescription::getCopy()
{
	return new NeuronDescription(inputFunction->getInputFunctionCopy(), activationFunction->getActivationFunctionCopy());
}

AbstractInputFunction* NeuronDescription::getInputFunction()
{
	return inputFunction.get();
}

AbstractActivationFunction* NeuronDescription::getActivationFunction()
{
	return activationFunction.get();
}
