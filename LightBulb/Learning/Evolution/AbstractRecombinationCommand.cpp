// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "AbstractEvolutionObject.hpp"


AbstractRecombinationCommand::AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, bool enableDebugOutput_) {
	recombinationAlgorithm.reset(recombinationAlgorithm_);
	recombinationSelector.reset(recombinationSelector_);
	enableDebugOutput = enableDebugOutput_;
}

void AbstractRecombinationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter, std::vector<AbstractEvolutionObject*>* notUsedObjects)
{
	if (highscore->size() > 0)
	{
		for (auto object = recombinationSelector->getRecombinationSelection()->begin(); object != recombinationSelector->getRecombinationSelection()->end(); object++)
		{
			// Clone the first objects and add it to the new object vector
			newObjectVector->push_back((*object)->clone());
			object++;
			// Also clone the second object
			AbstractEvolutionObject* secondClone = (*object)->clone();
			// Combine the two objects
			recombinationAlgorithm->execute(newObjectVector->back(), secondClone);

			delete(secondClone);
		}
	}
}