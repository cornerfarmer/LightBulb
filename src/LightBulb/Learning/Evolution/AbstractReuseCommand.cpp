// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"
#include "AbstractIndividual.hpp"

namespace LightBulb
{
	AbstractReuseCommand::AbstractReuseCommand(AbstractReuseSelector* reuseSelector_)
	{
		reuseSelector.reset(reuseSelector_);
	}

	AbstractReuseCommand::AbstractReuseCommand(const AbstractReuseCommand& other)
		:AbstractCommand(other)
	{
		reuseSelector.reset(dynamic_cast<AbstractReuseSelector*>(other.reuseSelector->clone()));
	}

	void swap(AbstractReuseCommand& lhs, AbstractReuseCommand& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractCommand&>(lhs), static_cast<AbstractCommand&>(rhs));
		swap(lhs.reuseSelector, rhs.reuseSelector);
	}

	void AbstractReuseCommand::execute(std::vector<AbstractIndividual*>& newIndividualVector, std::map<AbstractIndividual*, int>& counter, std::vector<AbstractIndividual*>& notUsedIndividuals)
	{
		for (auto individual = reuseSelector->getReuseSelection().begin(); individual != reuseSelector->getReuseSelection().end(); individual++)
		{
			if (counter[*individual] == 1)
			{
				newIndividualVector.push_back(*individual);
			}
			else
			{
				newIndividualVector.push_back(getUnusedIndividual(**individual, notUsedIndividuals));
			}
			newIndividualVector.back()->setEvolutionSource(Reuse);
			counter[*individual]--;
		}
	}
}
