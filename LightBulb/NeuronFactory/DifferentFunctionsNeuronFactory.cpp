// Includes
#include "NeuronFactory\DifferentFunctionsNeuronFactory.hpp"
#include "Neuron\InputNeuron.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Function\AbstractInputFunction.hpp"
#include "Function\AbstractActivationFunction.hpp"
#include "Function\AbstractOutputFunction.hpp"
#include "Neuron\AbstractThreshold.hpp"
// Library includes
#include <exception>


DifferentFunctionsNeuronFactory::DifferentFunctionsNeuronFactory(AbstractThreshold* thresholdInnerNeuron_, AbstractInputFunction* inputFunctionInnerNeuron_, AbstractActivationFunction* activationFunctionInnerNeuron_, AbstractOutputFunction* outputFunctionInnerNeuron_, AbstractThreshold* thresholdOutputNeuron_, AbstractInputFunction* inputFunctionOutputNeuron_, AbstractActivationFunction* activationFunctionOutputNeuron_, AbstractOutputFunction* outputFunctionOutputNeuron_)
{
	// Check if all given options are correct
	if (!thresholdInnerNeuron_)
		throw std::invalid_argument("The given thresholdInnerNeuron is not valid");
	if (!activationFunctionInnerNeuron_)
		throw std::invalid_argument("The given activationFunctionInnerNeuron is not valid");
	if (!inputFunctionInnerNeuron_)
		throw std::invalid_argument("The given inputFunctionInnerNeuron is not valid");
	if (!outputFunctionInnerNeuron_)
		throw std::invalid_argument("The given outputFunctionInnerNeuron is not valid");

	if (!thresholdOutputNeuron_)
		throw std::invalid_argument("The given thresholdOutputNeuron is not valid");
	if (!activationFunctionOutputNeuron_)
		throw std::invalid_argument("The given activationFunctionOutputNeuron is not valid");
	if (!inputFunctionOutputNeuron_)
		throw std::invalid_argument("The given inputFunctionOutputNeuron is not valid");
	if (!outputFunctionOutputNeuron_)
		throw std::invalid_argument("The given outputFunctionOutputNeuron is not valid");

	// Inner neurons
	thresholdInnerNeuron.reset(thresholdInnerNeuron_);
	activationFunctionInnerNeuron.reset(activationFunctionInnerNeuron_);
	inputFunctionInnerNeuron.reset(inputFunctionInnerNeuron_);
	outputFunctionInnerNeuron.reset(outputFunctionInnerNeuron_);
	// Output neurons
	thresholdOutputNeuron.reset(thresholdOutputNeuron_);
	activationFunctionOutputNeuron.reset(activationFunctionOutputNeuron_);
	inputFunctionOutputNeuron.reset(inputFunctionOutputNeuron_);
	outputFunctionOutputNeuron.reset(outputFunctionOutputNeuron_);
}

DifferentFunctionsNeuronFactory::DifferentFunctionsNeuronFactory(const DifferentFunctionsNeuronFactory &obj)
{
	// Inner neurons
	thresholdInnerNeuron.reset(obj.thresholdInnerNeuron->getCopy());
	activationFunctionInnerNeuron.reset(obj.activationFunctionInnerNeuron->getActivationFunctionCopy());
	inputFunctionInnerNeuron.reset(obj.inputFunctionInnerNeuron->getInputFunctionCopy());
	outputFunctionInnerNeuron.reset(obj.outputFunctionInnerNeuron->getOutputFunctionCopy());
	// Output neurons
	thresholdOutputNeuron.reset(obj.thresholdOutputNeuron->getCopy());
	activationFunctionOutputNeuron.reset(obj.activationFunctionOutputNeuron->getActivationFunctionCopy());
	inputFunctionOutputNeuron.reset(obj.inputFunctionOutputNeuron->getInputFunctionCopy());
	outputFunctionOutputNeuron.reset(obj.outputFunctionOutputNeuron->getOutputFunctionCopy());
}

InputNeuron* DifferentFunctionsNeuronFactory::createInputNeuron()
{
	return new InputNeuron();
}

StandardNeuron* DifferentFunctionsNeuronFactory::createInnerNeuron()
{
	return new StandardNeuron(thresholdInnerNeuron->getCopy(), inputFunctionInnerNeuron->getInputFunctionCopy(), activationFunctionInnerNeuron->getActivationFunctionCopy(), outputFunctionInnerNeuron->getOutputFunctionCopy());
}

StandardNeuron* DifferentFunctionsNeuronFactory::createOutputNeuron()
{
	return new StandardNeuron(thresholdOutputNeuron->getCopy(), inputFunctionOutputNeuron->getInputFunctionCopy(), activationFunctionOutputNeuron->getActivationFunctionCopy(), outputFunctionOutputNeuron->getOutputFunctionCopy());
}

AbstractNeuronFactory* DifferentFunctionsNeuronFactory::getCopy()
{
	return new DifferentFunctionsNeuronFactory(*this);
}