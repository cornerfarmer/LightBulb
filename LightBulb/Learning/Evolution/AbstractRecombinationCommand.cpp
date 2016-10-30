// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "AbstractEvolutionObject.hpp"

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

	void AbstractRecombinationCommand::execute(std::vector<AbstractEvolutionObject*>& newObjectVector, std::map<AbstractEvolutionObject*, int>& counter, std::vector<AbstractEvolutionObject*>& notUsedObjects)
	{
		AbstractEvolutionObject* firstParent;
		AbstractEvolutionObject* secondParent;
		for (auto object = recombinationSelector->getRecombinationSelection().begin(); object != recombinationSelector->getRecombinationSelection().end(); object++)
		{
			if (counter[*object] == 1)
			{
				firstParent = *object;
				counter[*object]--;
				object++;
				secondParent = *object;
				counter[*object]--;
				if (counter[*object] == 0)
				{
					notUsedObjects.push_back(*object);
				}
				recombinationAlgorithm->execute(*firstParent, *secondParent);
				newObjectVector.push_back(firstParent);
			}
			else
			{
				firstParent = *object;
				counter[*object]--;
				object++;
				if (counter[*object] == 1)
				{
					secondParent = *object;
					counter[*object]--;
					recombinationAlgorithm->execute(*secondParent, *firstParent);
					newObjectVector.push_back(secondParent);
				}
				else
				{
					secondParent = getUnusedObject(**object, notUsedObjects);
					counter[*object]--;
					recombinationAlgorithm->execute(*secondParent, *firstParent);
					newObjectVector.push_back(secondParent);
				}
			}
			newObjectVector.back()->setEvolutionSource(Recombination);
		}
	}

	void AbstractRecombinationCommand::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		recombinationAlgorithm->setRandomGenerator(randomGenerator_);
		recombinationSelector->setRandomGenerator(randomGenerator_);
	}
}