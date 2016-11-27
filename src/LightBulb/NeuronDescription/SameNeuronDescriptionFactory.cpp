// Includes
#include "NeuronDescription/SameNeuronDescriptionFactory.hpp"
#include "Function/InputFunction/AbstractInputFunction.hpp"
#include "NeuronDescription/NeuronDescription.hpp"
// Library includes

namespace LightBulb
{
	SameNeuronDescriptionFactory::SameNeuronDescriptionFactory(NeuronDescription* neuronDescription_)
	{
		// Check if all given options are correct
		if (!neuronDescription_)
			throw std::invalid_argument("The given neuronDescription is not valid");

		neuronDescription.reset(neuronDescription_);
	}

	SameNeuronDescriptionFactory::SameNeuronDescriptionFactory(const SameNeuronDescriptionFactory &obj)
	{
		neuronDescription.reset(dynamic_cast<NeuronDescription*>(obj.neuronDescription->clone()));
	}

	SameNeuronDescriptionFactory::SameNeuronDescriptionFactory(SameNeuronDescriptionFactory&& other) noexcept
		: SameNeuronDescriptionFactory()
	{
		swap(*this, other);
	}

	SameNeuronDescriptionFactory& SameNeuronDescriptionFactory::operator=(SameNeuronDescriptionFactory other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(SameNeuronDescriptionFactory& lhs, SameNeuronDescriptionFactory& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractNeuronDescriptionFactory&>(lhs), static_cast<AbstractNeuronDescriptionFactory&>(rhs));
		swap(lhs.neuronDescription, rhs.neuronDescription);
	}

	NeuronDescription* SameNeuronDescriptionFactory::createInnerNeuronDescription()
	{
		return dynamic_cast<NeuronDescription*>(neuronDescription->clone());
	}

	NeuronDescription* SameNeuronDescriptionFactory::createOutputNeuronDescription()
	{
		return dynamic_cast<NeuronDescription*>(neuronDescription->clone());
	}

	AbstractCloneable* SameNeuronDescriptionFactory::clone() const
	{
		return new SameNeuronDescriptionFactory(*this);
	}

	const AbstractActivationFunction& SameNeuronDescriptionFactory::getOutputActivationFunction() const
	{
		return neuronDescription->getActivationFunction();
	}

	const AbstractActivationFunction& SameNeuronDescriptionFactory::getInnerActivationFunction() const
	{
		return neuronDescription->getActivationFunction();
	}


	const AbstractInputFunction& SameNeuronDescriptionFactory::getOutputInputFunction() const
	{
		return neuronDescription->getInputFunction();
	}

	const AbstractInputFunction& SameNeuronDescriptionFactory::getInnerInputFunction() const
	{
		return neuronDescription->getInputFunction();
	}
}
