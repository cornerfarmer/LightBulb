// Includes
#include "Learning/Evolution/AbstractCommand.hpp"
#include "AbstractEvolutionObject.hpp"
#include <Logging/AbstractLogger.hpp>

AbstractEvolutionObject* AbstractCommand::getUnusedObject(AbstractEvolutionObject* usedObject, std::vector<AbstractEvolutionObject*>* notUsedObjects, bool addToWorld)
{
	if (notUsedObjects->empty())
	{
		return usedObject->clone(addToWorld);
	}
	else
	{
		AbstractEvolutionObject* notUsedObject = notUsedObjects->back();
		notUsedObjects->pop_back();
		notUsedObject->copyPropertiesFrom(usedObject);
		return notUsedObject;
	}
}
