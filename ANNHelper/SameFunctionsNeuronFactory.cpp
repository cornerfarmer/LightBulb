#include "SameFunctionsNeuronFactory.hpp"
#include "InputNeuron.hpp"
#include "StandardNeuron.hpp"
#include "AbstractInputFunction.hpp"
#include "AbstractActivationFunction.hpp"
#include "AbstractOutputFunction.hpp"
#include "AbstractThreshold.hpp"
#include <exception>

SameFunctionsNeuronFactory::SameFunctionsNeuronFactory(AbstractThreshold* threshold_, AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_, AbstractOutputFunction* outputFunction_)
{
	// Check if all given options are correct
	if (!threshold_)
		throw std::invalid_argument("The given threshold is not valid");
	if (!activationFunction_)
		throw std::invalid_argument("The given activationFunction is not valid");
	if (!inputFunction_)
		throw std::invalid_argument("The given inputFunction is not valid");
	if (!outputFunction_)
		throw std::invalid_argument("The given outputFunction is not valid");

	threshold.reset(threshold_);
	activationFunction.reset(activationFunction_);
	inputFunction.reset(inputFunction_);
	outputFunction.reset(outputFunction_);
}

SameFunctionsNeuronFactory::SameFunctionsNeuronFactory(const SameFunctionsNeuronFactory &obj)
{
	threshold.reset(obj.threshold->getCopy());
	activationFunction.reset(obj.activationFunction->getActivationFunctionCopy());
	inputFunction.reset(obj.inputFunction->getInputFunctionCopy());
	outputFunction.reset(obj.outputFunction->getOutputFunctionCopy());
}

InputNeuron* SameFunctionsNeuronFactory::createInputNeuron()
{
	return new InputNeuron();
}

StandardNeuron* SameFunctionsNeuronFactory::createInnerNeuron()
{
	return new StandardNeuron(threshold->getCopy(), inputFunction->getInputFunctionCopy(), activationFunction->getActivationFunctionCopy(), outputFunction->getOutputFunctionCopy());
}

StandardNeuron* SameFunctionsNeuronFactory::createOutputNeuron()
{
	return new StandardNeuron(threshold->getCopy(), inputFunction->getInputFunctionCopy(), activationFunction->getActivationFunctionCopy(), outputFunction->getOutputFunctionCopy());
}

AbstractNeuronFactory* SameFunctionsNeuronFactory::getCopy()
{
	return new SameFunctionsNeuronFactory(*this);
}