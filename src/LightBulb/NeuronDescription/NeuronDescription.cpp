// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/Function/InputFunction/AbstractInputFunction.hpp"
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"

namespace LightBulb
{
	NeuronDescription::NeuronDescription(AbstractInputFunction* inputFunction_, AbstractActivationFunction* activationFunction_)
	{
		inputFunction.reset(inputFunction_);
		activationFunction.reset(activationFunction_);
	}

	NeuronDescription::NeuronDescription(const NeuronDescription& other)
	{
		inputFunction.reset(dynamic_cast<AbstractInputFunction*>(other.inputFunction->clone()));
		activationFunction.reset(dynamic_cast<AbstractActivationFunction*>(other.activationFunction->clone()));
	}

	NeuronDescription::NeuronDescription(NeuronDescription&& other) noexcept
		: NeuronDescription()
	{
		swap(*this, other);
	}

	NeuronDescription& NeuronDescription::operator=(NeuronDescription other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(NeuronDescription& lhs, NeuronDescription& rhs) noexcept
	{
		using std::swap;
		swap(lhs.inputFunction, rhs.inputFunction);
		swap(lhs.activationFunction, rhs.activationFunction);
	}

	AbstractCloneable* NeuronDescription::clone() const
	{
		return new NeuronDescription(*this);
	}

	const AbstractInputFunction& NeuronDescription::getInputFunction() const
	{
		return *inputFunction.get();
	}

	const AbstractActivationFunction& NeuronDescription::getActivationFunction() const
	{
		return *activationFunction.get();
	}

	void NeuronDescription::setCalculatorType(const CalculatorType& calculatorType)
	{
		AbstractLinearAlgebraUser::setCalculatorType(calculatorType);
		activationFunction->setCalculatorType(calculatorType);
		inputFunction->setCalculatorType(calculatorType);
	}
}
