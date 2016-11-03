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
	class AbstractEvolutionObject;
	/**
	 * \brief This class is simplification of the AbstractEvolutionWorld class.
	 * \details/ It decreases the work you have to do for your world, but also decreases your possibilities.
	 * Nevertheless this class can be used in the most of all cases.
	 * It manages all evolution objects, so all inheriting classes can focus on evaluating those objects.
	 */
	class AbstractSimpleEvolutionWorld : public AbstractEvolutionWorld
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractSimpleEvolutionWorld const& world);
		template <class Archive>
		friend void load(Archive& archive, AbstractSimpleEvolutionWorld& world);
	protected:
		/**
		 * \brief A vector which contains all current evolution objects
		 */
		std::vector<AbstractEvolutionObject*> objects;
		/**
		 * \brief Creates new evolution object.
		 * \return The new object.
		 */
		virtual AbstractEvolutionObject* createNewObject() = 0;
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
		AbstractEvolutionObject* addNewObject(bool addToWorld = true) override;
		std::vector<AbstractEvolutionObject*>& getEvolutionObjects() override;
		void setEvolutionObjects(const std::vector<AbstractEvolutionObject*>& newObjects) override;
		void reset() override;
		int getPopulationSize() const override;
		void clearPopulation() override;
		void releaseAllObjects() override;
		void addExistingObject(AbstractEvolutionObject* newObject) override;
	};
}

#include "IO/AbstractSimpleEvolutionWorldIO.hpp"

#endif
