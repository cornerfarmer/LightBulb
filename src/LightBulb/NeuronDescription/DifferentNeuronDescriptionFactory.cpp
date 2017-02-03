// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp"
#include "LightBulb/Function/InputFunction/AbstractInputFunction.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
// Library includes

namespace LightBulb
{
	DifferentNeuronDescriptionFactory::DifferentNeuronDescriptionFactory() = default;

	DifferentNeuronDescriptionFactory::~DifferentNeuronDescriptionFactory() = default;

	DifferentNeuronDescriptionFactory::DifferentNeuronDescriptionFactory(NeuronDescription* innerNeuronDescription_, NeuronDescription* outputNeuronDescription_)
	{
		// Check if all given options are correct
		if (!innerNeuronDescription_)
			throw std::invalid_argument("The given innerNeuronDescription is not valid");
		if (!outputNeuronDescription_)
			throw std::invalid_argument("The given outputNeuronDescription is not valid");

		outputNeuronDescription.reset(outputNeuronDescription_);
		innerNeuronDescription.reset(innerNeuronDescription_);
	}

	DifferentNeuronDescriptionFactory::DifferentNeuronDescriptionFactory(const DifferentNeuronDescriptionFactory& other)
	{
		outputNeuronDescription.reset(dynamic_cast<NeuronDescription*>(other.outputNeuronDescription->clone()));
		innerNeuronDescription.reset(dynamic_cast<NeuronDescription*>(other.innerNeuronDescription->clone()));
	}

	DifferentNeuronDescriptionFactory::DifferentNeuronDescriptionFactory(DifferentNeuronDescriptionFactory&& other) noexcept
		: DifferentNeuronDescriptionFactory()
	{
		swap(*this, other);
	}

	DifferentNeuronDescriptionFactory& DifferentNeuronDescriptionFactory::operator=(DifferentNeuronDescriptionFactory other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(DifferentNeuronDescriptionFactory& lhs, DifferentNeuronDescriptionFactory& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractNeuronDescriptionFactory&>(lhs), static_cast<AbstractNeuronDescriptionFactory&>(rhs));
		swap(lhs.innerNeuronDescription, rhs.innerNeuronDescription);
		swap(lhs.outputNeuronDescription, rhs.outputNeuronDescription);
	}

	NeuronDescription* DifferentNeuronDescriptionFactory::createInnerNeuronDescription()
	{
		return dynamic_cast<NeuronDescription*>(innerNeuronDescription->clone());
	}

	NeuronDescription* DifferentNeuronDescriptionFactory::createOutputNeuronDescription()
	{
		return dynamic_cast<NeuronDescription*>(outputNeuronDescription->clone());
	}

	AbstractCloneable* DifferentNeuronDescriptionFactory::clone() const
	{
		return new DifferentNeuronDescriptionFactory(*this);
	}

	const AbstractActivationFunction& DifferentNeuronDescriptionFactory::getOutputActivationFunction() const
	{
		return outputNeuronDescription->getActivationFunction();
	}

	const AbstractActivationFunction& DifferentNeuronDescriptionFactory::getInnerActivationFunction() const
	{
		return innerNeuronDescription->getActivationFunction();
	}

	const AbstractInputFunction& DifferentNeuronDescriptionFactory::getOutputInputFunction() const
	{
		return outputNeuronDescription->getInputFunction();
	}

	const AbstractInputFunction& DifferentNeuronDescriptionFactory::getInnerInputFunction() const
	{
		return innerNeuronDescription->getInputFunction();
	}

	void DifferentNeuronDescriptionFactory::setCalculatorType(const CalculatorType& calculatorType)
	{
		AbstractLinearAlgebraUser::setCalculatorType(calculatorType);
		innerNeuronDescription->setCalculatorType(calculatorType);
		outputNeuronDescription->setCalculatorType(calculatorType);
	}
}
