// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/Learning/Evolution/AbstractRecombinationSelector.hpp"

//Library includes

namespace LightBulb
{
	ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int individualCount_)
		: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_)
	{
		recombinationPercentage = 0;
		individualCount = individualCount_;
	}

	ConstantRecombinationCommand::ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_)
		: AbstractRecombinationCommand(recombinationAlgorithm_, recombinationSelector_)
	{
		individualCount = 0;
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
		swap(lhs.individualCount, rhs.individualCount);
		swap(lhs.recombinationPercentage, rhs.recombinationPercentage);
	}

	void ConstantRecombinationCommand::select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter)
	{
		int individualCount = this->individualCount;
		// Calculate a temporary static individual count if the percentage value is used
		if (individualCount == 0)
			individualCount = highscore.size() * recombinationPercentage;
		recombinationSelector->executeRecombinationSelection(individualCount, highscore, counter);
	}

	AbstractCloneable* ConstantRecombinationCommand::clone() const
	{
		return new ConstantRecombinationCommand(*this);
	}
}
