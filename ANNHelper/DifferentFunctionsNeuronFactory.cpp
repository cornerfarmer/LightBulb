#include "DifferentFunctionsNeuronFactory.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "AbstractInputFunction.hpp"
#include "AbstractActivationFunction.hpp"
#include "AbstractOutputFunction.hpp"
#include <exception>


DifferentFunctionsNeuronFactory::DifferentFunctionsNeuronFactory(AbstractInputFunction* inputFunctionInnerNeuron_, AbstractActivationFunction* activationFunctionInnerNeuron_, AbstractOutputFunction* outputFunctionInnerNeuron_, AbstractInputFunction* inputFunctionOutputNeuron_, AbstractActivationFunction* activationFunctionOutputNeuron_, AbstractOutputFunction* outputFunctionOutputNeuron_)
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
	activationFunctionInnerNeuron = std::unique_ptr<AbstractActivationFunction>(activationFunctionInnerNeuron_);
	inputFunctionInnerNeuron = std::unique_ptr<AbstractInputFunction>(inputFunctionInnerNeuron_);
	outputFunctionInnerNeuron = std::unique_ptr<AbstractOutputFunction>(outputFunctionInnerNeuron_);
	// Functions for output neurons
	activationFunctionOutputNeuron = std::unique_ptr<AbstractActivationFunction>(activationFunctionOutputNeuron_);
	inputFunctionOutputNeuron = std::unique_ptr<AbstractInputFunction>(inputFunctionOutputNeuron_);
	outputFunctionOutputNeuron = std::unique_ptr<AbstractOutputFunction>(outputFunctionOutputNeuron_);
}

DifferentFunctionsNeuronFactory::DifferentFunctionsNeuronFactory(const DifferentFunctionsNeuronFactory &obj)
{
	activationFunctionInnerNeuron =std::unique_ptr<AbstractActivationFunction>(obj.activationFunctionInnerNeuron->getActivationFunctionCopy());
	inputFunctionInnerNeuron = std::unique_ptr<AbstractInputFunction>(obj.inputFunctionInnerNeuron->getInputFunctionCopy());
	outputFunctionInnerNeuron = std::unique_ptr<AbstractOutputFunction>(obj.outputFunctionInnerNeuron->getOutputFunctionCopy());

	activationFunctionOutputNeuron =std::unique_ptr<AbstractActivationFunction>(obj.activationFunctionOutputNeuron->getActivationFunctionCopy());
	inputFunctionOutputNeuron = std::unique_ptr<AbstractInputFunction>(obj.inputFunctionOutputNeuron->getInputFunctionCopy());
	outputFunctionOutputNeuron = std::unique_ptr<AbstractOutputFunction>(obj.outputFunctionOutputNeuron->getOutputFunctionCopy());
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

AbstractNeuronFactory* DifferentFunctionsNeuronFactory::getCopy()
{
	return new DifferentFunctionsNeuronFactory(*this);
}