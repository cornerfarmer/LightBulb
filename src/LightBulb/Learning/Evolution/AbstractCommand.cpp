// Includes
#include "Learning/Evolution/AbstractCommand.hpp"
#include "AbstractEvolutionObject.hpp"
#include <Logging/AbstractLogger.hpp>

namespace LightBulb
{
	AbstractEvolutionObject* AbstractCommand::getUnusedObject(AbstractEvolutionObject& usedObject, std::vector<AbstractEvolutionObject*>& notUsedObjects, bool addToWorld) const
	{
		if (notUsedObjects.empty())
		{
			return usedObject.clone(addToWorld);
		}
		else
		{
			AbstractEvolutionObject* notUsedObject = notUsedObjects.back();
			notUsedObjects.pop_back();
			notUsedObject->copyPropertiesFrom(usedObject);
			return notUsedObject;
		}
	}

	void swap(AbstractCommand& lhs, AbstractCommand& rhs) noexcept
	{
		using std::swap;
	}
}
