// Includes
#include "LightBulb/Learning/Evolution/AbstractSimpleEvolutionEnvironment.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"

namespace LightBulb
{
	AbstractIndividual* AbstractSimpleEvolutionEnvironment::addNewIndividual(bool addToEnvironment)
	{
		// Create a new individual
		AbstractIndividual* newIndividual = createNewIndividual();

		// Add it to the vector
		if (addToEnvironment)
			individuals.push_back(newIndividual);

		return newIndividual;
	}

	AbstractSimpleEvolutionEnvironment::AbstractSimpleEvolutionEnvironment()
	{

	}

	std::vector<AbstractIndividual*>& AbstractSimpleEvolutionEnvironment::getIndividuals()
	{
		return individuals;
	}

	void AbstractSimpleEvolutionEnvironment::setIndividuals(const std::vector<AbstractIndividual*>& newIndividuals)
	{
		individuals = newIndividuals;
	}

	void AbstractSimpleEvolutionEnvironment::reset()
	{
		// Reset all individuals
		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			(*individual)->resetNN();
		}
		// Reset the environment
		resetEnvironment();
	}

	int AbstractSimpleEvolutionEnvironment::getPopulationSize() const
	{
		return individuals.size();
	}


	void AbstractSimpleEvolutionEnvironment::clearPopulation()
	{
		individuals.clear();
	}

	void AbstractSimpleEvolutionEnvironment::addExistingIndividual(AbstractIndividual* newIndividual)
	{
		individuals.push_back(newIndividual);
	}
}
