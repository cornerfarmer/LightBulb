// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationCommand.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"

namespace LightBulb
{
	AbstractMutationCommand::AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_)
	{
		mutationAlgorithm.reset(mutationAlgorithm_);
		mutationSelector.reset(mutationSelector_);
	}

	AbstractMutationCommand::AbstractMutationCommand(const AbstractMutationCommand& other)
		:AbstractCommand(other)
	{
		mutationAlgorithm.reset(dynamic_cast<AbstractMutationAlgorithm*>(other.mutationAlgorithm->clone()));
		mutationSelector.reset(dynamic_cast<AbstractMutationSelector*>(other.mutationSelector->clone()));
	}

	void swap(AbstractMutationCommand& lhs, AbstractMutationCommand& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractCommand&>(lhs), static_cast<AbstractCommand&>(rhs));
		swap(lhs.mutationAlgorithm, rhs.mutationAlgorithm);
		swap(lhs.mutationSelector, rhs.mutationSelector);
	}

	void AbstractMutationCommand::execute(std::vector<AbstractIndividual*>& newIndividualVector, std::map<AbstractIndividual*, int>& counter, std::vector<AbstractIndividual*>& notUsedIndividuals)
	{
		for (auto individual = mutationSelector->getMutationSelection().begin(); individual != mutationSelector->getMutationSelection().end(); individual++)
		{
			if (counter[*individual] == 1)
			{
				mutationAlgorithm->execute(**individual);
				newIndividualVector.push_back(*individual);
			}
			else
			{
				AbstractIndividual* unusedIndividual = getUnusedIndividual(**individual, notUsedIndividuals);
				mutationAlgorithm->execute(*unusedIndividual);
				newIndividualVector.push_back(unusedIndividual);
			}
			newIndividualVector.back()->setEvolutionSource(Mutation);
			counter[*individual]--;
		}
	}

	void AbstractMutationCommand::setZigguratGenerator(ZigguratGenerator& zigguratGenerator)
	{
		mutationAlgorithm->setZigguratGenerator(zigguratGenerator);
	}

	void AbstractMutationCommand::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		mutationAlgorithm->setRandomGenerator(randomGenerator_);
		mutationSelector->setRandomGenerator(randomGenerator_);
	}

	void AbstractMutationCommand::setCalculatorType(const CalculatorType& calculatorType)
	{
		AbstractLinearAlgebraUser::setCalculatorType(calculatorType);
		mutationAlgorithm->setCalculatorType(calculatorType);
	}
}
