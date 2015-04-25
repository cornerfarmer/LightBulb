#include "DifferentFunctionsNeuronFactory.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"

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
	return new StandardNeuron(inputFunctionInnerNeuron, activationFunctionInnerNeuron, outputFunctionInnerNeuron);
}

StandardNeuron* DifferentFunctionsNeuronFactory::createOutputNeuron()
{
	return new StandardNeuron(inputFunctionOutputNeuron, activationFunctionOutputNeuron, outputFunctionOutputNeuron);
}