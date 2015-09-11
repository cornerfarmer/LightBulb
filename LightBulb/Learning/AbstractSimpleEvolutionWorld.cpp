// Includes
#include "Learning\AbstractSimpleEvolutionWorld.hpp"
#include "Learning\EvolutionObjectInterface.hpp"


EvolutionObjectInterface* AbstractSimpleEvolutionWorld::addNewObject()
{
	objects.push_back(createNewObject());
	
	return objects.back();
}

AbstractSimpleEvolutionWorld::AbstractSimpleEvolutionWorld()
{	

}

std::vector<EvolutionObjectInterface*>* AbstractSimpleEvolutionWorld::getEvolutionObjects()
{
	return &objects;
}

void AbstractSimpleEvolutionWorld::setEvolutionObjects(std::vector<EvolutionObjectInterface*>& newObjects)
{
	objects = newObjects;
}

void AbstractSimpleEvolutionWorld::reset()
{
	for (auto object = objects.begin(); object != objects.end(); object++)
	{
		(*object)->resetNN();
	}
	resetWorld();
}
