// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"


AbstractEvolutionObject* AbstractSimpleEvolutionWorld::addNewObject()
{
	// Create a new object and add it to the vector
	objects.push_back(createNewObject());
	
	return objects.back();
}

AbstractSimpleEvolutionWorld::AbstractSimpleEvolutionWorld()
{	

}

std::vector<AbstractEvolutionObject*>* AbstractSimpleEvolutionWorld::getEvolutionObjects()
{
	return &objects;
}

void AbstractSimpleEvolutionWorld::setEvolutionObjects(std::vector<AbstractEvolutionObject*>& newObjects)
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
