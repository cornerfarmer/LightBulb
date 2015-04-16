#include "SameFunctionsNeuronFactory.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"

SameFunctionsNeuronFactory::SameFunctionsNeuronFactory(InputFunction* inputFunction_, ActivationFunction* activationFunction_, OutputFunction* outputFunction_)
{
	activationFunction = activationFunction_;
	inputFunction = inputFunction_;
	outputFunction = outputFunction_;
}

InputNeuron* SameFunctionsNeuronFactory::createInputNeuron()
{
	return new InputNeuron();
}

StandardNeuron* SameFunctionsNeuronFactory::createInnerNeuron()
{
	return new StandardNeuron(inputFunction, activationFunction, outputFunction);
}

StandardNeuron* SameFunctionsNeuronFactory::createOutputNeuron()
{
	return new StandardNeuron(inputFunction, activationFunction, outputFunction);
}