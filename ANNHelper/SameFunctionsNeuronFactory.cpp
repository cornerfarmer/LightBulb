#include "SameFunctionsNeuronFactory.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "AbstractInputFunction.hpp"
#include "AbstractActivationFunction.hpp"
#include "AbstractOutputFunction.hpp"
#include <exception>

SameFunctionsNeuronFactory::SameFunctionsNeuronFactory(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_)
{
	// Check if all given options are correct
	if (!activationFunction_)
		throw std::invalid_argument("The given activationFunction is not valid");
	if (!inputFunction_)
		throw std::invalid_argument("The given inputFunction is not valid");
	if (!outputFunction_)
		throw std::invalid_argument("The given outputFunction is not valid");

	activationFunction = std::unique_ptr<AbstractActivationFunction>(activationFunction_);
	inputFunction = std::unique_ptr<AbstractInputFunction>(inputFunction_);
	outputFunction = std::unique_ptr<AbstractOutputFunction>(outputFunction_);
}

SameFunctionsNeuronFactory::SameFunctionsNeuronFactory(const SameFunctionsNeuronFactory &obj)
{
	activationFunction =std::unique_ptr<AbstractActivationFunction>(obj.activationFunction->getActivationFunctionCopy());
	inputFunction = std::unique_ptr<AbstractInputFunction>(obj.inputFunction->getInputFunctionCopy());
	outputFunction = std::unique_ptr<AbstractOutputFunction>(obj.outputFunction->getOutputFunctionCopy());
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

AbstractNeuronFactory* SameFunctionsNeuronFactory::getCopy()
{
	return new SameFunctionsNeuronFactory(*this);
}