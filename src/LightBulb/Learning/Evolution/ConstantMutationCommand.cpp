// Includes
#include "LightBulb/Learning/Evolution/ConstantMutationCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
//Library includes

namespace LightBulb
{
	ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, int individualCount_)
		: AbstractMutationCommand(mutationAlgorithm_, mutationSelector_)
	{
		mutationPercentage = 0;
		individualCount = individualCount_;
	}

	ConstantMutationCommand::ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, double mutationPercentage_)
		: AbstractMutationCommand(mutationAlgorithm_, mutationSelector_)
	{
		individualCount = 0;
		mutationPercentage = mutationPercentage_;
	}

	ConstantMutationCommand::ConstantMutationCommand(ConstantMutationCommand&& other) noexcept
		: ConstantMutationCommand()
	{
		swap(*this, other);
	}

	ConstantMutationCommand& ConstantMutationCommand::operator=(ConstantMutationCommand other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(ConstantMutationCommand& lhs, ConstantMutationCommand& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractMutationCommand&>(lhs), static_cast<AbstractMutationCommand&>(rhs));
		swap(lhs.individualCount, rhs.individualCount);
		swap(lhs.mutationPercentage, rhs.mutationPercentage);
	}

	void ConstantMutationCommand::select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter)
	{
		int individualCount = this->individualCount;
		// Calculate a temporary static individual count if the percentage value is used
		if (individualCount == 0)
			individualCount = highscore.size() * mutationPercentage;

		mutationSelector->executeMutationSelection(individualCount, highscore, counter);

		mutationAlgorithm->initialize(highscore);
	}

	AbstractCloneable* ConstantMutationCommand::clone() const
	{
		return new ConstantMutationCommand(*this);
	}

}
