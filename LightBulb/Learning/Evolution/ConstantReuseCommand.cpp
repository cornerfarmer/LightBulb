// Includes
#include "Learning/Evolution/ConstantReuseCommand.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes

namespace LightBulb
{
	ConstantReuseCommand::ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, int objectCount_)
		: AbstractReuseCommand(reuseSelector_)
	{
		setReuseCount(objectCount_);
	}

	ConstantReuseCommand::ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, double reusePercentage_)
		: AbstractReuseCommand(reuseSelector_)
	{
		setReusePercentage(reusePercentage_);
	}

	ConstantReuseCommand::ConstantReuseCommand(ConstantReuseCommand&& other) noexcept
		: ConstantReuseCommand()
	{
		swap(*this, other);
	}

	ConstantReuseCommand& ConstantReuseCommand::operator=(ConstantReuseCommand other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(ConstantReuseCommand& lhs, ConstantReuseCommand& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractReuseCommand&>(lhs), static_cast<AbstractReuseCommand&>(rhs));
		swap(lhs.objectCount, rhs.objectCount);
		swap(lhs.reusePercentage, rhs.reusePercentage);
	}

	void ConstantReuseCommand::select(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter)
	{
		int objectCount = this->objectCount;
		// Calculate a temporary static object count if the percentage value is used
		if (objectCount == 0)
			objectCount = highscore.size() * reusePercentage;

		reuseSelector->executeReuseSelection(objectCount, highscore, counter);
	}

	void ConstantReuseCommand::setReusePercentage(double newReusePercentage)
	{
		objectCount = 0;
		reusePercentage = newReusePercentage;
	}

	void ConstantReuseCommand::setReuseCount(double newReuseCount)
	{
		reusePercentage = 0;
		objectCount = newReuseCount;
	}

	AbstractCloneable* ConstantReuseCommand::clone() const
	{
		return new ConstantReuseCommand(*this);
	}

}
