// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"
#include "AbstractEvolutionObject.hpp"

namespace LightBulb
{
	AbstractReuseCommand::AbstractReuseCommand(AbstractReuseSelector* reuseSelector_)
	{
		reuseSelector.reset(reuseSelector_);
	}

	void AbstractReuseCommand::execute(std::vector<AbstractEvolutionObject*>& newObjectVector, std::map<AbstractEvolutionObject*, int>& counter, std::vector<AbstractEvolutionObject*>& notUsedObjects)
	{
		for (auto object = reuseSelector->getReuseSelection().begin(); object != reuseSelector->getReuseSelection().end(); object++)
		{
			if (counter[*object] == 1)
			{
				newObjectVector.push_back(*object);
			}
			else
			{
				newObjectVector.push_back(getUnusedObject(**object, notUsedObjects));
			}
			newObjectVector.back()->setEvolutionSource(Reuse);
			counter[*object]--;
		}
	}

}