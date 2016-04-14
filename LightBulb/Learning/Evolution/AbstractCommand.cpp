// Includes
#include "Learning/Evolution/AbstractCommand.hpp"
#include "AbstractEvolutionObject.hpp"
#include <Logging/AbstractLogger.hpp>

AbstractEvolutionObject* AbstractCommand::getUnusedObject(AbstractEvolutionObject* usedObject, std::vector<AbstractEvolutionObject*>* notUsedObjects)
{
	if (notUsedObjects->empty())
	{
		return usedObject->clone();
	}
	else
	{
		AbstractEvolutionObject* notUsedObject = notUsedObjects->back();
		notUsedObjects->pop_back();
		notUsedObject->copyPropertiesFrom(usedObject);
		return notUsedObject;
	}
}
