// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"

namespace LightBulb
{
	AbstractEvolutionObject* AbstractSimpleEvolutionWorld::addNewObject(bool addToWorld)
	{
		// Create a new object
		AbstractEvolutionObject* newObject = createNewObject();

		// Add it to the vector
		if (addToWorld)
			objects.push_back(newObject);

		return newObject;
	}

	AbstractSimpleEvolutionWorld::AbstractSimpleEvolutionWorld()
	{

	}

	std::vector<AbstractEvolutionObject*>* AbstractSimpleEvolutionWorld::getEvolutionObjects()
	{
		return &objects;
	}

	void AbstractSimpleEvolutionWorld::setEvolutionObjects(const std::vector<AbstractEvolutionObject*>& newObjects)
	{
		objects = newObjects;
	}

	void AbstractSimpleEvolutionWorld::reset()
	{
		// Reset all objects
		for (auto object = objects.begin(); object != objects.end(); object++)
		{
			(*object)->resetNN();
		}
		// Reset the world
		resetWorld();
	}

	int AbstractSimpleEvolutionWorld::getPopulationSize()
	{
		return objects.size();
	}


	void AbstractSimpleEvolutionWorld::clearPopulation()
	{
		objects.clear();
	}

	void AbstractSimpleEvolutionWorld::releaseAllObjects()
	{
		objects.clear();
	}

	void AbstractSimpleEvolutionWorld::addExistingObject(AbstractEvolutionObject* newObject)
	{
		objects.push_back(newObject);
	}
}
