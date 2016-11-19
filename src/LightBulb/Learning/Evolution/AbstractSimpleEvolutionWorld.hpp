#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONWORLD_H_
#define _ABSTRACTSIMPLEEVOLUTIONWORLD_H_

// Library Includes
#include <vector>

// Include
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractIndividual;
	/**
	 * \brief This class is simplification of the AbstractEvolutionWorld class.
	 * \details It decreases the work you have to do for your world, but also decreases your possibilities.
	 * Nevertheless this class can be used in the most of all cases.
	 * It manages all individuals, so all inheriting classes can focus on evaluating those individuals.
	 */
	class AbstractSimpleEvolutionWorld : public AbstractEvolutionWorld
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractSimpleEvolutionWorld const& world);
		template <class Archive>
		friend void load(Archive& archive, AbstractSimpleEvolutionWorld& world);
	protected:
		/**
		 * \brief A vector which contains all current individuals.
		 */
		std::vector<AbstractIndividual*> individuals;
		/**
		 * \brief Creates new individual.
		 * \return The new individual.
		 */
		virtual AbstractIndividual* createNewIndividual() = 0;
		/**
		 * \brief Resets the world before doing any simulations.
		 */
		virtual void resetWorld() {};
	public:
		/**
		 * \brief Creates the simple evolution world.
		 */
		AbstractSimpleEvolutionWorld();
		// Inherited:
		AbstractIndividual* addNewIndividual(bool addToWorld = true) override;
		std::vector<AbstractIndividual*>& getIndividuals() override;
		void setIndividuals(const std::vector<AbstractIndividual*>& newIndividuals) override;
		void reset() override;
		int getPopulationSize() const override;
		void clearPopulation() override;
		void addExistingIndividual(AbstractIndividual* newIndividual) override;
	};
}

#include "IO/AbstractSimpleEvolutionWorldIO.hpp"

#endif
