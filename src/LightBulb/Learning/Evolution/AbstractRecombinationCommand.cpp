// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"

namespace LightBulb
{

	AbstractRecombinationCommand::AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_) {
		recombinationAlgorithm.reset(recombinationAlgorithm_);
		recombinationSelector.reset(recombinationSelector_);
	}

	AbstractRecombinationCommand::AbstractRecombinationCommand(const AbstractRecombinationCommand& other)
		:AbstractCommand(other)
	{
		recombinationAlgorithm.reset(dynamic_cast<AbstractRecombinationAlgorithm*>(other.recombinationAlgorithm->clone()));
		recombinationSelector.reset(dynamic_cast<AbstractRecombinationSelector*>(other.recombinationSelector->clone()));
	}

	void swap(AbstractRecombinationCommand& lhs, AbstractRecombinationCommand& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractCommand&>(lhs), static_cast<AbstractCommand&>(rhs));
		swap(lhs.recombinationAlgorithm, rhs.recombinationAlgorithm);
		swap(lhs.recombinationSelector, rhs.recombinationSelector);
	}

	void AbstractRecombinationCommand::execute(std::vector<AbstractIndividual*>& newIndividualVector, std::map<AbstractIndividual*, int>& counter, std::vector<AbstractIndividual*>& notUsedIndividuals)
	{
		AbstractIndividual* firstParent;
		AbstractIndividual* secondParent;
		for (auto individual = recombinationSelector->getRecombinationSelection().begin(); individual != recombinationSelector->getRecombinationSelection().end(); individual++)
		{
			if (counter[*individual] == 1)
			{
				firstParent = *individual;
				counter[*individual]--;
				individual++;
				secondParent = *individual;
				counter[*individual]--;
				if (counter[*individual] == 0)
				{
					notUsedIndividuals.push_back(*individual);
				}
				recombinationAlgorithm->execute(*firstParent, *secondParent);
				newIndividualVector.push_back(firstParent);
			}
			else
			{
				firstParent = *individual;
				counter[*individual]--;
				individual++;
				if (counter[*individual] == 1)
				{
					secondParent = *individual;
					counter[*individual]--;
					recombinationAlgorithm->execute(*secondParent, *firstParent);
					newIndividualVector.push_back(secondParent);
				}
				else
				{
					secondParent = getUnusedIndividual(**individual, notUsedIndividuals);
					counter[*individual]--;
					recombinationAlgorithm->execute(*secondParent, *firstParent);
					newIndividualVector.push_back(secondParent);
				}
			}
			newIndividualVector.back()->setEvolutionSource(Recombination);
		}
	}

	void AbstractRecombinationCommand::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		recombinationAlgorithm->setRandomGenerator(randomGenerator_);
		recombinationSelector->setRandomGenerator(randomGenerator_);
	}

}
