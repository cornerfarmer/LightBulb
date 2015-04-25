#include "SameFunctionsNeuronFactory.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "InputFunction.hpp"
#include "ActivationFunction.hpp"
#include "OutputFunction.hpp"
#include <exception>

SameFunctionsNeuronFactory::~SameFunctionsNeuronFactory()
{
	delete(activationFunction);
	delete(inputFunction);
	delete(outputFunction);
}

SameFunctionsNeuronFactory::SameFunctionsNeuronFactory(InputFunction* inputFunction_, ActivationFunction* activationFunction_, OutputFunction* outputFunction_)
{
	// Check if all given options are correct
	if (!activationFunction_)
		throw std::exception();
	if (!inputFunction_)
		throw std::exception();
	if (!outputFunction_)
		throw std::exception();

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
	return new StandardNeuron(inputFunction->getInputFunctionCopy(), activationFunction->getActivationFunctionCopy(), outputFunction->getOutputFunctionCopy());
}

StandardNeuron* SameFunctionsNeuronFactory::createOutputNeuron()
{
	return new StandardNeuron(inputFunction->getInputFunctionCopy(), activationFunction->getActivationFunctionCopy(), outputFunction->getOutputFunctionCopy());
}