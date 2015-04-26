#include "DifferentFunctionsNeuronFactory.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "InputFunction.hpp"
#include "ActivationFunction.hpp"
#include "OutputFunction.hpp"
#include <exception>

DifferentFunctionsNeuronFactory::~DifferentFunctionsNeuronFactory()
{
	delete(activationFunctionInnerNeuron);
	delete(inputFunctionInnerNeuron);
	delete(outputFunctionInnerNeuron);

	delete(activationFunctionOutputNeuron);
	delete(inputFunctionOutputNeuron);
	delete(outputFunctionOutputNeuron);
}

DifferentFunctionsNeuronFactory::DifferentFunctionsNeuronFactory(InputFunction* inputFunctionInnerNeuron_, ActivationFunction* activationFunctionInnerNeuron_, OutputFunction* outputFunctionInnerNeuron_, InputFunction* inputFunctionOutputNeuron_, ActivationFunction* activationFunctionOutputNeuron_, OutputFunction* outputFunctionOutputNeuron_)
{
	// Check if all given options are correct
	if (!activationFunctionInnerNeuron_)
		throw std::invalid_argument("The given activationFunctionInnerNeuron is not valid");
	if (!inputFunctionInnerNeuron_)
		throw std::invalid_argument("The given inputFunctionInnerNeuron is not valid");
	if (!outputFunctionInnerNeuron_)
		throw std::invalid_argument("The given outputFunctionInnerNeuron is not valid");
	if (!activationFunctionOutputNeuron_)
		throw std::invalid_argument("The given activationFunctionOutputNeuron is not valid");
	if (!inputFunctionOutputNeuron_)
		throw std::invalid_argument("The given inputFunctionOutputNeuron is not valid");
	if (!outputFunctionOutputNeuron_)
		throw std::invalid_argument("The given outputFunctionOutputNeuron is not valid");

	// Functions for inner neurons
	activationFunctionInnerNeuron = activationFunctionInnerNeuron_;
	inputFunctionInnerNeuron = inputFunctionInnerNeuron_;
	outputFunctionInnerNeuron = outputFunctionInnerNeuron_;
	// Functions for output neurons
	activationFunctionOutputNeuron = activationFunctionOutputNeuron_;
	inputFunctionOutputNeuron = inputFunctionOutputNeuron_;
	outputFunctionOutputNeuron = outputFunctionOutputNeuron_;
}

InputNeuron* DifferentFunctionsNeuronFactory::createInputNeuron()
{
	return new InputNeuron();
}

StandardNeuron* DifferentFunctionsNeuronFactory::createInnerNeuron()
{
	return new StandardNeuron(inputFunctionInnerNeuron->getInputFunctionCopy(), activationFunctionInnerNeuron->getActivationFunctionCopy(), outputFunctionInnerNeuron->getOutputFunctionCopy());
}

StandardNeuron* DifferentFunctionsNeuronFactory::createOutputNeuron()
{
	return new StandardNeuron(inputFunctionOutputNeuron->getInputFunctionCopy(), activationFunctionOutputNeuron->getActivationFunctionCopy(), outputFunctionOutputNeuron->getOutputFunctionCopy());
}