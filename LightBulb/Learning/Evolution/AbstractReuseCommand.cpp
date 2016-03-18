// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"
#include "AbstractEvolutionObject.hpp"

AbstractReuseCommand::AbstractReuseCommand(AbstractReuseSelector* reuseSelector_,bool enableDebugOutput_)
{
	enableDebugOutput = enableDebugOutput_;
	reuseSelector.reset(reuseSelector_);
}

void AbstractReuseCommand::execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector)
{
	for (auto object = reuseSelector->getReuseSelection()->begin(); object != reuseSelector->getReuseSelection()->end(); object++)
	{
		// Move the object to the new vector
		newObjectVector->push_back((*object)->clone());
	}
}
