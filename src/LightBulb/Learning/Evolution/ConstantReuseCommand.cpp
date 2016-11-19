// Includes
#include "Learning/Evolution/ConstantReuseCommand.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
//Library includes

namespace LightBulb
{
	ConstantReuseCommand::ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, int individualCount_)
		: AbstractReuseCommand(reuseSelector_)
	{
		reusePercentage = 0;
		individualCount = individualCount_;
	}

	ConstantReuseCommand::ConstantReuseCommand(AbstractReuseSelector* reuseSelector_, double reusePercentage_)
		: AbstractReuseCommand(reuseSelector_)
	{
		individualCount = 0;
		reusePercentage = reusePercentage_;
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
		swap(lhs.individualCount, rhs.individualCount);
		swap(lhs.reusePercentage, rhs.reusePercentage);
	}

	void ConstantReuseCommand::select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter)
	{
		int individualCount = this->individualCount;
		// Calculate a temporary static individual count if the percentage value is used
		if (individualCount == 0)
			individualCount = highscore.size() * reusePercentage;

		reuseSelector->executeReuseSelection(individualCount, highscore, counter);
	}

	AbstractCloneable* ConstantReuseCommand::clone() const
	{
		return new ConstantReuseCommand(*this);
	}

}
