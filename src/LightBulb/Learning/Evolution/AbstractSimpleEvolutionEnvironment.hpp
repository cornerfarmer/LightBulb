#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONENVIRONMENT_H_
#define _ABSTRACTSIMPLEEVOLUTIONENVIRONMENT_H_

// Library Includes
#include <vector>

// Include
#include "Learning/Evolution/AbstractEvolutionEnvironment.hpp"

namespace LightBulb
{
	// Forward declarations
	class EvolutionLearningRule;
	class AbstractIndividual;
	/**
	 * \brief This class is simplification of the AbstractEvolutionEnvironment class.
	 * \details It decreases the work you have to do for your environment, but also decreases your possibilities.
	 * Nevertheless this class can be used in the most of all cases.
	 * It manages all individuals, so all inheriting classes can focus on evaluating those individuals.
	 */
	class AbstractSimpleEvolutionEnvironment : public AbstractEvolutionEnvironment
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractSimpleEvolutionEnvironment const& environment);
		template <class Archive>
		friend void load(Archive& archive, AbstractSimpleEvolutionEnvironment& environment);
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
		 * \brief Resets the environment before doing any simulations.
		 */
		virtual void resetEnvironment() {};
	public:
		/**
		 * \brief Creates the simple evolution environment.
		 */
		AbstractSimpleEvolutionEnvironment();
		// Inherited:
		AbstractIndividual* addNewIndividual(bool addToEnvironment = true) override;
		std::vector<AbstractIndividual*>& getIndividuals() override;
		void setIndividuals(const std::vector<AbstractIndividual*>& newIndividuals) override;
		void reset() override;
		int getPopulationSize() const override;
		void clearPopulation() override;
		void addExistingIndividual(AbstractIndividual* newIndividual) override;
	};
}

#include "IO/AbstractSimpleEvolutionEnvironmentIO.hpp"

#endif
