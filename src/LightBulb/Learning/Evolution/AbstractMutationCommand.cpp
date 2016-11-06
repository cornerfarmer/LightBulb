// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "AbstractEvolutionObject.hpp"

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

	void AbstractMutationCommand::execute(std::vector<AbstractEvolutionObject*>& newObjectVector, std::map<AbstractEvolutionObject*, int>& counter, std::vector<AbstractEvolutionObject*>& notUsedObjects)
	{
		for (auto object = mutationSelector->getMutationSelection().begin(); object != mutationSelector->getMutationSelection().end(); object++)
		{
			if (counter[*object] == 1)
			{
				mutationAlgorithm->execute(**object);
				newObjectVector.push_back(*object);
			}
			else
			{
				AbstractEvolutionObject* unusedObject = getUnusedObject(**object, notUsedObjects);
				mutationAlgorithm->execute(*unusedObject);
				newObjectVector.push_back(unusedObject);
			}
			newObjectVector.back()->setEvolutionSource(Mutation);
			counter[*object]--;
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

}
