// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "AbstractEvolutionObject.hpp"

AbstractMutationCommand::AbstractMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, bool enableDebugOutput_)
{
	mutationAlgorithm.reset(mutationAlgorithm_);
	mutationSelector.reset(mutationSelector_);
	enableDebugOutput = enableDebugOutput_;
}

void AbstractMutationCommand::setMutationSelector(AbstractMutationSelector* mutationSelector_)
{
	mutationSelector.release();
	mutationSelector.reset(mutationSelector_);
}


void AbstractMutationCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	if (highscore->size() > 0)
	{
		for (auto object = mutationSelector->getMutationSelection()->begin(); object != mutationSelector->getMutationSelection()->end(); object++)
		{
			// Clone it and add it to the new object vector
			newObjectVector->push_back((*object)->clone());
			// Mutate the new object
			mutationAlgorithm->execute(newObjectVector->back());
		}
	}
}