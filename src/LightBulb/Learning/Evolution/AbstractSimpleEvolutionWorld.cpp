// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"

namespace LightBulb
{
	AbstractIndividual* AbstractSimpleEvolutionWorld::addNewIndividual(bool addToWorld)
	{
		// Create a new individual
		AbstractIndividual* newIndividual = createNewIndividual();

		// Add it to the vector
		if (addToWorld)
			individuals.push_back(newIndividual);

		return newIndividual;
	}

	AbstractSimpleEvolutionWorld::AbstractSimpleEvolutionWorld()
	{

	}

	std::vector<AbstractIndividual*>& AbstractSimpleEvolutionWorld::getIndividuals()
	{
		return individuals;
	}

	void AbstractSimpleEvolutionWorld::setIndividuals(const std::vector<AbstractIndividual*>& newIndividuals)
	{
		individuals = newIndividuals;
	}

	void AbstractSimpleEvolutionWorld::reset()
	{
		// Reset all individuals
		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			(*individual)->resetNN();
		}
		// Reset the world
		resetWorld();
	}

	int AbstractSimpleEvolutionWorld::getPopulationSize() const
	{
		return individuals.size();
	}


	void AbstractSimpleEvolutionWorld::clearPopulation()
	{
		individuals.clear();
	}

	void AbstractSimpleEvolutionWorld::addExistingIndividual(AbstractIndividual* newIndividual)
	{
		individuals.push_back(newIndividual);
	}
}
