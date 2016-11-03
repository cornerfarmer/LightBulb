// Includes
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes

namespace LightBulb
{
	ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int objectCount_)
		: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_)
	{
		recombinationPercentage = 0;
		objectCount = objectCount_;
	}

	ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_)
		: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_)
	{
		objectCount = 0;
		recombinationPercentage = recombinationPercentage_;
	}

	ConstantRecombinationCommand::ConstantRecombinationCommand(ConstantRecombinationCommand&& other) noexcept
		: ConstantRecombinationCommand()
	{
		swap(*this, other);
	}

	ConstantRecombinationCommand& ConstantRecombinationCommand::operator=(ConstantRecombinationCommand other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(ConstantRecombinationCommand& lhs, ConstantRecombinationCommand& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractRecombinationCommand&>(lhs), static_cast<AbstractRecombinationCommand&>(rhs));
		swap(lhs.objectCount, rhs.objectCount);
		swap(lhs.recombinationPercentage, rhs.recombinationPercentage);
	}

	void ConstantRecombinationCommand::select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter)
	{
		int objectCount = this->objectCount;
		// Calculate a temporary static object count if the percentage value is used
		if (objectCount == 0)
			objectCount = highscore.size() * recombinationPercentage;
		recombinationSelector->executeRecombinationSelection(objectCount, highscore, counter);
	}

	AbstractCloneable* ConstantRecombinationCommand::clone() const
	{
		return new ConstantRecombinationCommand(*this);
	}
}
