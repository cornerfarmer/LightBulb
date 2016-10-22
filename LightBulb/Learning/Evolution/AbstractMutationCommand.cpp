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

	void AbstractMutationCommand::setMutationSelector(AbstractMutationSelector* mutationSelector_)
	{
		mutationSelector.release();
		mutationSelector.reset(mutationSelector_);
	}


	void AbstractMutationCommand::execute(std::vector<AbstractEvolutionObject*>* newObjectVector, std::map<AbstractEvolutionObject*, int>* counter, std::vector<AbstractEvolutionObject*>* notUsedObjects)
	{
		for (auto object = mutationSelector->getMutationSelection()->begin(); object != mutationSelector->getMutationSelection()->end(); object++)
		{
			if ((*counter)[*object] == 1)
			{
				mutationAlgorithm->execute(*object);
				newObjectVector->push_back(*object);
			}
			else
			{
				AbstractEvolutionObject* unusedObject = getUnusedObject(*object, notUsedObjects);
				mutationAlgorithm->execute(unusedObject);
				newObjectVector->push_back(unusedObject);
			}
			newObjectVector->back()->setEvolutionSource(Mutation);
			(*counter)[*object]--;
		}
	}

	void AbstractMutationCommand::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		mutationAlgorithm->setRandomGenerator(randomGenerator_);
		mutationSelector->setRandomGenerator(randomGenerator_);
	}
}